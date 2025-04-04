// Shoot Then Up Game, All Rights Reserved

#include "Services/ResourceLoaderService.h"
#include "Engine/StreamableManager.h"
#include "Helpers/Constants.h"

UResourceLoaderService::UResourceLoaderService()
{
    ResourceMap = TMap<FName, UDataAsset*>();
}

void UResourceLoaderService::LoadResources()
{
    const FSoftObjectPath ConfigPath(Constants::CharacterConfig);

    if(!ConfigPath.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Character Config Path"));
        return;
    }

    if (ResourceMap.Contains(Constants::CharacterConfig))
        return;

    
    TSharedPtr<FStreamableHandle> Handle =
        StreamableManager.RequestAsyncLoad(ConfigPath, FStreamableDelegate :: CreateLambda(
                                                           [this, ConfigPath]()
                                                           {
                                                               if (UDataAsset* Config = Cast<UDataAsset>(ConfigPath.TryLoad()))
                                                               {
                                                                   ResourceMap.Add(Constants::CharacterConfig, Config);
                                                                   OnCharacterConfigLoaded.Broadcast();
                                                                   UE_LOG(LogTemp, Warning, TEXT("Loaded Character Config"));
                                                               }
                                                               else
                                                               {
                                                                   UE_LOG(LogTemp, Error, TEXT("Failed to load Character Config")); 
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




