// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/HealthInterface.h"
#include "Parameters/FHealthParameters.h"
#include "Parameters/FHealthRecoveryParameters.h"
#include "STUHealthComponent.generated.h"

class UTweenService;
class UEventBusService;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USTUHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FHealthParameters HealthParameters;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FHealthRecoveryParameters HealthRecoveryParameters;
    
	USTUHealthComponent();
    
    virtual float GetHealth() const override { return HealthParameters.Health; }

    UFUNCTION(BlueprintCallable)
    virtual bool IsDead() const override { return HealthParameters.Health <= 0.0f; }

protected:
	virtual void BeginPlay() override;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser
    );

private:
    FTimerHandle RecoveryTimerHandle;
    UTweenService* TweenService;

    void RecoveryHealth() const;
    void StartHealthRecoveryTimer();
};
