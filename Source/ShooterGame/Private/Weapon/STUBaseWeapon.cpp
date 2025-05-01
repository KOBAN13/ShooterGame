// Shoot Then Up Game, All Rights Reserved

#include "STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMeshComponent);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Warning, TEXT("Fire"));
}

