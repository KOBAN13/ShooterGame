// Shoot Then Up Game, All Rights Reserved

#include "STUGameInstance.h"

#include "ObjectEventBusService.h"
#include "ResourceLoaderService.h"
#include "ServiceLocatorSubsystem.h"
#include "StructEventBusService.h"
#include "TweenService.h"
#include "VoidEventBusService.h"

void USTUGameInstance::Init()

{
    Super::Init();

    ServiceLocatorSubsystem = GetSubsystem<UServiceLocatorSubsystem>();

    ServiceLocatorSubsystem->RegisterService<UTweenService>(GetWorld(), UTweenService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UResourceLoaderService>(GetWorld(), UResourceLoaderService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UObjectEventBusService>(GetWorld(), UObjectEventBusService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UVoidEventBusService>(GetWorld(), UObjectEventBusService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UStructEventBusService>(GetWorld(), UObjectEventBusService::StaticClass());
    
    UResourceLoaderService* ResourceLoaderService = nullptr;
    
    ServiceLocatorSubsystem -> TryGetService(ResourceLoaderService);

    ResourceLoaderService -> LoadResources();
}

UServiceLocatorSubsystem* USTUGameInstance::GetServiceLocator() const
{
    return ServiceLocatorSubsystem;
}
