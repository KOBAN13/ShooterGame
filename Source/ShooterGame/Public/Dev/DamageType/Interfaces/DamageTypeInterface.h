// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EDamageCategory.h"
#include "UObject/Interface.h"
#include "DamageTypeInterface.generated.h"

UINTERFACE(MinimalAPI)
class UDamageTypeInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IDamageTypeInterface
{
	GENERATED_BODY()

public:
    virtual EDamageCategory GetDamageCategory() const = 0;
};
