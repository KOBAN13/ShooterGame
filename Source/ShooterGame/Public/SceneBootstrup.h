// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneBootstrup.generated.h"

class UServiceLocator;

UCLASS()
class SHOOTERGAME_API ASceneBootstrup : public AActor
{
    GENERATED_BODY()

public:
    ASceneBootstrup();

protected:
    virtual void BeginPlay() override;
};
