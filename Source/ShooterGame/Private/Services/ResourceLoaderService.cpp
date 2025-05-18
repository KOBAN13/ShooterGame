// Shoot Then Up Game, All Rights Reserved

#include "ResourceLoaderService.h"
#include "Engine/StreamableManager.h"

UResourceLoaderService::UResourceLoaderService()
{
    ResourceMap = TMap<FName, UDataAsset*>();
}

void UResourceLoaderService::LoadResources(const FName& Name,  FSimpleDelegate OnConfigLoaded)
{
    const FSoftObjectPath ConfigPath(Name);

    if(!ConfigPath.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Character Config Path"));
        return;
    }   

    if (ResourceMap.Contains(Name))
        return;

    
    TSharedPtr<FStreamableHandle> Handle =
        StreamableManager.RequestAsyncLoad(ConfigPath, FStreamableDelegate :: CreateLambda(
                                                           [this, ConfigPath, Name, OnConfigLoaded]()
                                                           {
                                                               if (UDataAsset* Config = Cast<UDataAsset>(ConfigPath.TryLoad()))
                                                               {
                                                                   ResourceMap.Add(Name, Config);
                                                                   OnConfigLoaded.Execute();
                                                                   UE_LOG(LogTemp, Warning, TEXT("Loaded %s"), *Name.ToString());
                                                               }
                                                               else
                                                               {
                                                                   UE_LOG(LogTemp, Error, TEXT("Failed loaded to %s"), *Name.ToString()); 
                                                               }
                                                           }));
}

UDataAsset* UResourceLoaderService::GetResource(FName Name)
{
    if(ResourceMap.Contains(Name))
    {
        return ResourceMap[Name];
    }

    return nullptr;
}




