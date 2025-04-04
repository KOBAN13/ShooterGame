// Shoot Then Up Game, All Rights Reserved

#include "Services/STUGameInstance.h"

#include "ResourceLoaderService.h"
#include "TweenService.h"
#include "Services/ServiceLocatorSubsystem.h"


void USTUGameInstance::Init()
{
    Super::Init();

    ServiceLocatorSubsystem = GetSubsystem<UServiceLocatorSubsystem>();

    ServiceLocatorSubsystem->RegisterService<UTweenService>(UTweenService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UResourceLoaderService>(UResourceLoaderService::StaticClass());

    UResourceLoaderService* ResourceLoaderService = nullptr;
    
    ServiceLocatorSubsystem -> TryGetService(ResourceLoaderService);

    ResourceLoaderService -> LoadResources();
}

UServiceLocatorSubsystem* USTUGameInstance::GetServiceLocator() const
{
    return ServiceLocatorSubsystem;
}
