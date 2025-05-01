// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMeshComponent;
    
	virtual void BeginPlay() override;
};
