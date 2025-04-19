// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFireDamageType.h"
#include "STUIceDamageType.h"
#include "STUHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUHealthComponent();
    float GetHealth() const { return Health; }
    
protected:
    UPROPERTY(
        EditDefaultsOnly,
        BlueprintReadWrite,
        meta = (ClampMin = "0.0", ClampMax = "500.0"), Category = "Health"
    )
    float MaxHealth = 100.0f;
    
	virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser
    );
};
