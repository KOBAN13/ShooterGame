// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLogs, All, All);

class UCharacterConfig;
class UCameraComponent;
class USpringArmComponent;
class UServiceLocatorSubsystem;

UCLASS()
class SHOOTERGAME_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY()
    UCharacterConfig* CharacterConfig;

    UPROPERTY()
    UServiceLocatorSubsystem* ServiceLocator;

private:
    int32 IdTweenRunStart = 0;
    int32 IdTweenRunEnd = 0;

protected:
    virtual void BeginPlay() override;

public:
    ASTUBaseCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void LookUp(float Amount);
    void TurnAround(float Amount);
    void BindInputAxis(UInputComponent* PlayerInputComponent);
    void CreateComponentsAndAttach();
    void RunStart();
    void RunEnd();

    void LoadConfigs();
};
