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
    
    if(ServiceManager.IsValid())
    {
        UServiceManager* ServiceManagerPtr = ServiceManager.Get();
        ServiceManagerPtr -> RegisterService<UTestService>(UTestService::StaticClass());
    }

    UTestService* TestService;

    if(ServiceManager.IsValid() && ServiceManager -> TryGetService<UTestService>(TestService))
    {
        TestService -> WorkService();
    }
}

void ASceneBootstrup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
