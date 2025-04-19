// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUFireDamageType.h"
#include "STUIceDamageType.h"
#include "Interfaces/HealthInterface.h"
#include "STUHealthComponent.generated.h"

USTRUCT(BlueprintType)
struct FHealthParameters
{
    GENERATED_BODY()

    UPROPERTY(
    EditDefaultsOnly,
    BlueprintReadWrite,
    meta = (ClampMin = "0.0", ClampMax = "500.0"), Category = "Health")
    float Health = 0.0f;

    UPROPERTY(
    EditDefaultsOnly,
    BlueprintReadWrite,
    meta = (ClampMin = "0.0", ClampMax = "500.0"), Category = "Health")
    float MaxHealth = 100.0f;
};

class UEventBusService;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USTUHealthComponent : public UActorComponent, public IHealthInterface
{
	GENERATED_BODY()

public:
    UPROPERTY()
    UEventBusService* EventBus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FHealthParameters HealthParameters;
    
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
};
