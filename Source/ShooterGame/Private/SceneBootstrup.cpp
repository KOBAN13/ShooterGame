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

    if (ServiceManager.IsValid())
    {
        UServiceManager* ServiceManagerPtr = ServiceManager.Get();
        ServiceManagerPtr -> RegisterService<UTestService>(UTestService::StaticClass());
    }

    UTestService* TestService;

    if (ServiceManager.IsValid() && ServiceManager->TryGetService<UTestService>(TestService))
    {
        if(TestService == nullptr)
            return;
        
        TestService->WorkService();
        
        ServiceManager -> UnregisterService<UTestService>(TestService,
            OnServiceUnregistered::CreateLambda([]
            {
                UE_LOG(LogTemp, Warning, TEXT("Service %s unregistered"),
                    *UTestService::StaticClass()->GetName());
            }));
    }
}

void ASceneBootstrup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
