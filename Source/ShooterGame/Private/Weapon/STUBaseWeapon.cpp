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

    check(WeaponMeshComponent)
}

void ASTUBaseWeapon::Fire()
{
    UE_LOG(LogBaseWeapon, Warning, TEXT("Fire"));

    MakeShot();
}

void ASTUBaseWeapon::MakeShot()
{
    const auto* World = GetWorld();
    const auto* Player = Cast<ACharacter>(GetOwner());
    const auto Controller = Player -> GetController<APlayerController>();

    if(!World || !Player | !Controller)
        return;

    FVector ViewLocation;
    FRotator ViewRotation;
    
    Controller -> GetPlayerViewPoint(ViewLocation, ViewRotation);

    const FTransform MuzzleFlashSocketTransform = WeaponMeshComponent -> GetSocketTransform(MuzzleFlashSocketName);

    const FVector TraceStart = ViewLocation;
    const FVector TraceDirection = ViewRotation.Vector();
    const FVector TraceEnd = TraceStart + TraceDirection * TraceMaxDistance;

    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams . AddIgnoredActor(GetOwner());
    
    FHitResult HitResult;
    
    World -> LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

    if(HitResult.bBlockingHit)
    {
        DrawDebugLine(World, MuzzleFlashSocketTransform.GetLocation(), HitResult.ImpactPoint, FColor::Red, false, 2.0f, 0, 2.0f);
        DrawDebugSphere(World, HitResult.ImpactPoint, 3.0f, 12, FColor::Red, false, 2.0f);
    }
    else
    {
        DrawDebugLine(World, MuzzleFlashSocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 2.0f, 0, 2.0f);
    }

    //ОТРЕФАКТОРИТЬ И ИСПРАВИТЬ ПРОБЛЕМУ С ТЕМ ЧТО МЫ МОЖЕМ ПОПАСТЬ ВО ВРАГА БУДУЧИ ЗА НИМ МОЖНО ЧЕРЕЗ УГОЛ
}

