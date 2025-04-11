// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

class UCharacterConfig;
class UServiceLocatorSubsystem;

UCLASS()
class SHOOTERGAME_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

    UPROPERTY()
    UCharacterConfig* CharacterConfig;

    UPROPERTY()
    UServiceLocatorSubsystem* ServiceLocator;
    int32 IdTweenRunStart = 0;
    int32 IdTweenRunEnd = 0;
    float MaxSpeed;
    
    void OnCharacterConfigLoaded();
    void Initialize();
    
    virtual void InitializeComponent() override;
    
    void RunStart(USTUCharacterMovementComponent* Component);
    void RunEnd(USTUCharacterMovementComponent* Component);
    
public:
    void HandleMovementEvent(UObject* MovementEvent);
};
