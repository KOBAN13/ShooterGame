// Shoot Then Up Game, All Rights Reserved

#include "STUBaseWeapon.h"

#include "EventBusMacros.h"
#include "EventNameConstants.h"
#include "ResourceLoaderService.h"
#include "STUCharacterMovementComponent.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "Engine/DamageEvents.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMeshComponent);
}

void ASTUBaseWeapon::Initialize()
{
    if(auto* World = GetWorld())
    {
        Subscribe_Void(EventNameConstants::OnBaseWeaponConfigLoaded, 1, [this]() { OnBaseWeaponConfig(); }, World);
    }
}

void ASTUBaseWeapon::OnBaseWeaponConfig()
{
    
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMeshComponent)
}

void ASTUBaseWeapon::StartFire()
{
    GetWorldTimerManager()
    .SetTimer(
        ShotTimerHandle,
        this,
        &ASTUBaseWeapon::MakeShot,
        TimeBetweenShots,
        true
    );
}

void ASTUBaseWeapon::StopFire()
{
    GetWorldTimerManager()
    .ClearTimer(ShotTimerHandle);
}

void ASTUBaseWeapon::MakeShot()
{
    if (!CanShoot())
        return;

    FVector TraceStart, TraceEnd;
    GetTraceData(TraceStart, TraceEnd);

    FHitResult HitResult;
    PerformLineTrace(TraceStart, TraceEnd, HitResult);

    SetDamage(&HitResult);

    DrawShotVisuals(HitResult, TraceEnd);
}

void ASTUBaseWeapon::SetDamage(const FHitResult* HitResult)
{
    auto* HitActor = HitResult -> GetActor();

    if (!HitActor)
        return;
    
    HitActor -> TakeDamage(10.0f, FDamageEvent{}, nullptr, this);
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
    const auto* Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;

    return Player->GetController<APlayerController>();
}

bool ASTUBaseWeapon::CanShoot() const
{
    const auto* World = GetWorld();
    if (!World)
        return false;

    const auto Controller = GetPlayerController();
    return Controller != nullptr;
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    const auto* Controller = GetPlayerController();
    
    if (!Controller)
        return false;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller -> GetPlayerViewPoint(ViewLocation, ViewRotation);

    const auto HalfRad = FMath::DegreesToRadians(BulletSpreadInRadians);
    const auto ShotDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceStart = ViewLocation;
    TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
    return true;
}

void ASTUBaseWeapon::PerformLineTrace(const FVector& TraceStart, const FVector& TraceEnd, FHitResult& HitResult) const
{
    const auto* World = GetWorld();

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    World->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::DrawShotVisuals(const FHitResult& HitResult, const FVector& TraceEnd) const
{
    const FTransform MuzzleFlashSocketTransform = WeaponMeshComponent -> GetSocketTransform(MuzzleFlashSocketName);
    const auto* World = GetWorld();
    
    if(HitResult.bBlockingHit)
    {
        DrawDebugLine(
            World,
            MuzzleFlashSocketTransform.GetLocation(),
            HitResult.ImpactPoint,
            FColor::Red,
            false,
            2.0f,
            0,
            2.0f
        );
        
        DrawDebugSphere(
            World,
            HitResult.ImpactPoint,
            5.0f,
            24,
            FColor::Red,
            false,
            2.0f
        );
    }
    else
    {
        DrawDebugLine(
            World,
            MuzzleFlashSocketTransform.GetLocation(),
            TraceEnd,
            FColor::Red,
            false,
            2.0f,
            0,
            2.0f
        );
    }
}

