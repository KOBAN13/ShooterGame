#include "SceneBootstrup.h"

#include "UServiceManager.h"
#include "UTestService.h"

ASceneBootstrup::ASceneBootstrup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASceneBootstrup::BeginPlay()
{
    Super::BeginPlay();
}
