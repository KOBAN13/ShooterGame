#include "SceneBootstrup.h"

#include "UServiceManager.h"
#include "UTestService.h"

ASceneBootstrup::ASceneBootstrup()
{
    PrimaryActorTick.bCanEverTick = true;

    ServiceManager = NewObject<UServiceManager>();
}

void ASceneBootstrup::BeginPlay()
{
    Super::BeginPlay();

    ServiceManager -> RegisterService<UTestService>(UTestService::StaticClass());
}

void ASceneBootstrup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
