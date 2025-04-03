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
    FStreamableManager StreamableManager;

    const FSoftObjectPath ConfigPath(Constants::CharacterConfig);
    TSharedPtr<FStreamableHandle> Handle =
        StreamableManager.RequestAsyncLoad(ConfigPath, FStreamableDelegate ::CreateLambda(
                                                           [this, &Handle]()
                                                           {
                                                               if (!ResourceMap.Contains(Constants::CharacterConfig))
                                                               {
                                                                   if (UDataAsset* Config = Cast<UDataAsset>(Handle->GetLoadedAsset()))
                                                                   {
                                                                       ResourceMap.Add(Constants::CharacterConfig, Config);
                                                                   }
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




