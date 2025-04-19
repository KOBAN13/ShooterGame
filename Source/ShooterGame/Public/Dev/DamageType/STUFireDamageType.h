// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EDamageCategory.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/DamageTypeInterface.h"
#include "STUFireDamageType.generated.h"

enum class EDamageCategory : uint8;

UCLASS()
class SHOOTERGAME_API USTUFireDamageType : public UDamageType, public IDamageTypeInterface
{
	GENERATED_BODY()

public:
    virtual EDamageCategory GetDamageCategory() const override { return EDamageCategory::Fire; }
};
