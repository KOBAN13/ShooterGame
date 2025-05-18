// Shoot Then Up Game, All Rights Reserved

#include "STUGameInstance.h"

#include "ConstantsLoader.h"
#include "EventBusMacros.h"
#include "EventNameConstants.h"
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
    ServiceLocatorSubsystem->RegisterService<UVoidEventBusService>(GetWorld(), UVoidEventBusService::StaticClass());
    ServiceLocatorSubsystem->RegisterService<UStructEventBusService>(GetWorld(), UStructEventBusService::StaticClass());
    
    UResourceLoaderService* ResourceLoaderService = nullptr;
    
    ServiceLocatorSubsystem -> TryGetService(ResourceLoaderService);

    ResourceLoaderService -> LoadResources(ConstantsLoader::CharacterConfig,
        FSimpleDelegate::CreateLambda([this]()
        {
            SendEvent_Void(EventNameConstants::OnCharacterConfigLoaded, GetWorld());
        }));
    
    ResourceLoaderService -> LoadResources(ConstantsLoader::BaseWeaponConfig,
        FSimpleDelegate::CreateLambda([this]()
        {
            SendEvent_Void(EventNameConstants::OnBaseWeaponConfigLoaded, GetWorld());
        }));
}

UServiceLocatorSubsystem* USTUGameInstance::GetServiceLocator() const
{
    return ServiceLocatorSubsystem.Get();
}
