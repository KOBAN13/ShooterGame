// Shoot Then Up Game, All Rights Reserved

#include "Component/STUHealthComponent.h"

#include "EventBusService.h"
#include "EventNameConstants.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"

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

    if (const auto* World = GetWorld())
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World -> GetGameInstance()))
        {
            if (const auto* ServiceLocator = GameInstance->GetServiceLocator();
                ServiceLocator -> TryGetService(EventBus))
            {
                check(EventBus);
            }
        }
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if(Damage <= 0.0f || IsDead()) return;

    HealthParameters.Health = FMath::Clamp(HealthParameters.Health - Damage, 0.0f, HealthParameters.MaxHealth);

    EventBus -> SendEventStruct<FHealthParameters>(EventNameConstants::OnHealthChanged, &HealthParameters);

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

    if(IsDead())
    {
        EventBus -> SendEvent(EventNameConstants::OnCharacterDead);
    }
}

