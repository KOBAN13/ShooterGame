// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UTextRenderComponent;
class USTUHealthComponent;
class UCharacterConfig;
class UCameraComponent;
class USpringArmComponent;
class UServiceLocatorSubsystem;
class UEventBusService;
class USTUCharacterMovementComponent;

UCLASS()
class SHOOTERGAME_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUCharacterMovementComponent* CharacterMovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY()
    UCharacterConfig* CharacterConfig;

    UPROPERTY()
    UEventBusService* EventBus;
    
private:
    bool bIsWalk = false;
    bool bIsRun = false;
    
public:
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetWalkDirection() const;
    
    ASTUBaseCharacter(const FObjectInitializer &ObjectInitializer);

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override; 

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void LookUp(float Amount);
    void TurnAround(float Amount);
    void BindInputAxis(UInputComponent* PlayerInputComponent);
    void CreateComponentsAndAttach();
    void RunStart();
    void RunEnd();
};
