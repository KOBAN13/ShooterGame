// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

class UServiceLocatorSubsystem;

UCLASS()
class SHOOTERGAME_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
    
    UServiceLocatorSubsystem* GetServiceLocatorSubsystem() const;
};