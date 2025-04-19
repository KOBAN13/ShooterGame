// Shoot Then Up Game, All Rights Reserved

#include "Component/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    
    Health = MaxHealth;

    if (AActor* Owner = GetOwner())
    {
        Owner -> OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
    AController* InstigatedBy, AActor* DamageCauser)
{
    Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

    if (const IDamageTypeInterface* DamageTypeInterface = Cast<IDamageTypeInterface>(DamageType))
    {
        switch (DamageTypeInterface -> GetDamageCategory())
        {
            case EDamageCategory::Fire:
                UE_LOG(LogHealthComponent, Warning, TEXT("Take Fire Damage"));
                break;
            
            case EDamageCategory::Ice:
                UE_LOG(LogHealthComponent, Warning, TEXT("Take Ice Damage"));
                break;
            
            default: break;
        }
    }
}

