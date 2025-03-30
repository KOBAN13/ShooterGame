// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterConfig.generated.h"

UCLASS(BlueprintType, Config = Game)
class SHOOTERGAME_API UCharacterConfig : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Character")
	float MaxSpeed = 600.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Character")
    float RunSpeed = 800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "Character")
    float TimeInterpolation = 0.5f;
};
