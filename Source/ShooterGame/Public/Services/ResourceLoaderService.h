// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ResourceLoaderService.generated.h"


UCLASS()
class SHOOTERGAME_API UResourceLoaderService : public UObject
{
	GENERATED_BODY()

    UResourceLoaderService();

private:
    UPROPERTY()
        TMap<FString, FSoftObjectPath> ResourceMap;
};
