// Shoot Then Up Game, All Rights Reserved

#include "Component/STUHealthComponent.h"

#include "EventBusMacros.h"
#include "EventNameConstants.h"
#include "STUIceDamageType.h"
#include "ServiceLocatorHelper.h"
#include "StructEventBusService.h"
#include "TweenService.h"

class UVoidEventBusService;
USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    if (AActor* Owner = GetOwner())
    {
        Owner -> OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }

    TweenService = TryGetService<UTweenService>(GetWorld());
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead())
        return;

    HealthParameters.Health = FMath::Clamp(HealthParameters.Health - Damage, 0.0f, HealthParameters.MaxHealth);

    StartHealthRecoveryTimer();

    SendEvent_OneParam<FHealthParameters, UStructEventBusService>(EventNameConstants::OnHealthChanged, GetWorld(), &HealthParameters);

    if (const IDamageTypeInterface* DamageTypeInterface = Cast<IDamageTypeInterface>(DamageType))
    {
        switch (DamageTypeInterface->GetDamageCategory())
        {
            case EDamageCategory::Fire:
                UE_LOG(LogHealthComponent, Warning, TEXT("Take Fire Damage"));
            break;
            
            case EDamageCategory::Ice:
                UE_LOG(LogHealthComponent, Warning, TEXT("Take Ice Damage"));
            break;

            default:
                break;
        }
    }

    if (IsDead())
    {
        SendEvent_Void(EventNameConstants::OnCharacterDead, GetWorld());
        
        TweenService -> SteppedTweenKill(TweenId);
    }
}

void USTUHealthComponent::StartHealthRecoveryTimer()
{
    if(!HealthRecoveryParameters.IsAutoHeal || HealthParameters.Health >= HealthParameters.MaxHealth)
        return;

    TweenService -> SteppedTweenKill(TweenId);
    
    TweenId = TweenService -> SteppedTweenFloat(
        HealthParameters.Health,
        HealthParameters.MaxHealth,
        HealthRecoveryParameters.HealModifier,
        HealthRecoveryParameters.HealUpdateTime,
        HealthRecoveryParameters.HealDelay,
        [this](const float Health)
        {
            HealthParameters.Health = Health;

            SendEvent_OneParam<FHealthParameters, UStructEventBusService>(EventNameConstants::OnHealthChanged, GetWorld(), &HealthParameters);
            
            GEngine -> AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Health: ") + FString::SanitizeFloat(Health));
        }
        );
}

