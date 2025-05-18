// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "ResourceLoaderService.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCharacterConfigLoaded);

UCLASS()
class SHOOTERGAME_API UResourceLoaderService : public UObject
{
	GENERATED_BODY()

    UResourceLoaderService();
    
    UPROPERTY()
    TMap<FName, UDataAsset*> ResourceMap;
    FStreamableManager StreamableManager;

public:
    UDataAsset* GetResource(FName Name);
    void LoadResources(const FName& Name,  FSimpleDelegate OnConfigLoaded);

    FOnCharacterConfigLoaded OnCharacterConfigLoaded;
};
