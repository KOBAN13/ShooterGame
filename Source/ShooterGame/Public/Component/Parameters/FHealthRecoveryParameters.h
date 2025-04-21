#pragma once

#include "CoreMinimal.h"
#include "FHealthRecoveryParameters.generated.h"

USTRUCT(BlueprintType)
struct FHealthRecoveryParameters
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    bool IsAutoHeal = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float HealDelay = 0.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float HealUpdateTime = 0.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float HealModifier = 0.0f;
};
