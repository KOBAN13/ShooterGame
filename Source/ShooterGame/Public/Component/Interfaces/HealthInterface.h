// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IHealthInterface
{
	GENERATED_BODY()
    
public:
    virtual float GetHealth() const = 0;
    virtual bool IsDead() const = 0;
};
