// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "STUBaseWeapon.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogBaseWeapon, All, All);

class USkeletalMeshComponent;

UCLASS()
class SHOOTERGAME_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

    virtual void Fire();
    virtual void MakeShot();
    virtual void SetDamage(const FHitResult* HitResult);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleFlashSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.f;
    
	virtual void BeginPlay() override;

private:
    APlayerController* GetPlayerController() const;
    bool CanShoot() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void PerformLineTrace(
        const FVector& TraceStart,
        const FVector& TraceEnd,
        FHitResult& HitResult
    ) const;
    void DrawShotVisuals(const FHitResult& HitResult, const FVector& TraceEnd) const;
};
