#pragma once

#include "CoreMinimal.h"
#include "FHealthParameters.generated.h"

USTRUCT(BlueprintType)
struct FHealthParameters
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Health = 0.0f;

    UPROPERTY(
    EditDefaultsOnly,
    BlueprintReadWrite,
    meta = (ClampMin = "0.0", ClampMax = "500.0"), Category = "Health")
    float MaxHealth = 100.0f;
};
