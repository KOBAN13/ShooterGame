// Shoot Then Up Game, All Rights Reserved

#include "STUWeaponComponent.h"
#include "STUBaseWeapon.h"
#include "STUBaseCharacter.h"

USTUWeaponComponent::USTUWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CreateWeapon();
}

void USTUWeaponComponent::CreateWeapon()
{
    auto* World = GetWorld();
    const auto* Character = Cast<ASTUBaseCharacter>(GetOwner());
    
    check(World)
    check(Cast<ACharacter>(GetOwner()))
    
    CurrentWeapon = World -> SpawnActor<ASTUBaseWeapon>(WeaponClass);

    check(CurrentWeapon.Get())
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);

    CurrentWeapon -> AttachToComponent(Character -> GetMesh(), AttachmentRules, WeaponSocketName);
}

void USTUWeaponComponent::Fire()
{
    CurrentWeapon -> Fire();
}



