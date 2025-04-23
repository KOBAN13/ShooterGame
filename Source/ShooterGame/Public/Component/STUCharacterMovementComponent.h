// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TweenService.h"
#include "STUCharacterMovementComponent.generated.h"

class UResourceLoaderService;
class UTweenService;
class UCharacterConfig;
class UServiceLocatorSubsystem;

UCLASS()
class SHOOTERGAME_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

    UPROPERTY()
    UCharacterConfig* CharacterConfig;

    UPROPERTY()
    UTweenService* TweenService;

    UPROPERTY()
    UResourceLoaderService* ResourceLoaderService;
    
    int32 IdTweenRunStart = 0;
    int32 IdTweenRunEnd = 0;
    float MaxSpeed;
    
    void OnCharacterConfigLoaded();
    void Initialize();
    
    virtual void InitializeComponent() override;
    
    void RunStart();
    void RunEnd();
};
