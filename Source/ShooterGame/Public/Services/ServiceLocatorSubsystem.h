// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServiceLocatorSubsystem.generated.h"

class UServiceManager;
UCLASS()
class SHOOTERGAME_API UServiceLocatorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
    
    TWeakObjectPtr<UServiceManager> ServiceManager;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
