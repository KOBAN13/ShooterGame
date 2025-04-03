// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "ResourceLoaderService.generated.h"


UCLASS()
class SHOOTERGAME_API UResourceLoaderService : public UObject
{
	GENERATED_BODY()

    UResourceLoaderService();
    
    UPROPERTY()
    TMap<FName, UDataAsset*> ResourceMap;
    void LoadResources();
    FStreamableManager StreamableManager;

public:
    UDataAsset* GetResource(FName Name);
};
