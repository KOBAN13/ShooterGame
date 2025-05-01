// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUWeaponComponent();

    void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASTUBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponSocketName = "WeaponSocket";
    
	virtual void BeginPlay() override;

private:
    TWeakObjectPtr<ASTUBaseWeapon> CurrentWeapon;
    
    void CreateWeapon();
};
