// Shoot Then Up Game, All Rights Reserved

#include "STUGameInstance.h"

#include "ResourceLoaderService.h"
#include "TweenService.h"
#include "ServiceLocatorSubsystem.h"


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
