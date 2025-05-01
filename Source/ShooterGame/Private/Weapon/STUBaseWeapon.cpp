// Shoot Then Up Game, All Rights Reserved

#include "STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
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

