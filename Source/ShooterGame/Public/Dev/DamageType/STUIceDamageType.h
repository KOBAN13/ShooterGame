// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EDamageCategory.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/DamageTypeInterface.h"
#include "STUIceDamageType.generated.h"

enum class EDamageCategory : uint8;

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UCLASS()
class SHOOTERGAME_API USTUIceDamageType : public UDamageType, public IDamageTypeInterface
{
	GENERATED_BODY()

public:
    virtual EDamageCategory GetDamageCategory() const override { return EDamageCategory::Ice; }
};
