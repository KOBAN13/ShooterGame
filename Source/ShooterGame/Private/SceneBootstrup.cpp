#include "SceneBootstrup.h"

#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "UServiceManager.h"
#include "UTestService.h"

ASceneBootstrup::ASceneBootstrup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASceneBootstrup::BeginPlay()
{
    Super::BeginPlay();

    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    UServiceLocatorSubsystem * ServiceLocatorSubsystem = GameInstance -> GetServiceLocatorSubsystem();

    if(ServiceLocatorSubsystem->IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("ServiceLocatorSubsystem is not valid"));
        return;
    }
    
    UServiceManager* ServiceManager = ServiceLocatorSubsystem -> GetServiceManager();

    if(ServiceManager -> IsValidLowLevel() == false)
    {
        UE_LOG(LogTemp, Warning, TEXT("ServiceManager is not valid"));
        return;
    }
    
    ServiceLocatorSubsystem -> RegisterService<UTestService>(UTestService::StaticClass());
    
    UTestService* TestService = nullptr;
    ServiceLocatorSubsystem -> TryGetService<UTestService>(TestService);
    TestService -> WorkService();

    ServiceLocatorSubsystem -> UnregisterService<UTestService>(TestService,
        OnServiceUnregistered::CreateLambda([]()
        {
            UE_LOG(LogTemp, Warning, TEXT("Service %s unregistered"),
                *UTestService::StaticClass()->GetName());
        }));
}