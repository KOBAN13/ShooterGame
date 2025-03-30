#include "SceneBootstrup.h"

#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "TweenService.h"

ASceneBootstrup::ASceneBootstrup()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASceneBootstrup::BeginPlay()
{
    Super::BeginPlay();

    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    UServiceLocatorSubsystem * ServiceLocatorSubsystem = GameInstance -> GetServiceLocatorSubsystem();
    
    ServiceLocatorSubsystem -> RegisterService<UTweenService>(UTweenService::StaticClass());
}