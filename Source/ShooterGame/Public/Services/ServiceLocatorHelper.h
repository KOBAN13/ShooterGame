#pragma once

#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"

template <typename T>
FORCEINLINE T* TryGetService(UWorld* World)
{
    if (!World)
    {
        return nullptr;
    }

    const auto* GameInstance = Cast<USTUGameInstance>(World->GetGameInstance());
    if (!GameInstance)
    {
        return nullptr;
    }

    UServiceLocatorSubsystem* ServiceLocator = GameInstance->GetServiceLocator();
    if (!ServiceLocator)
    {
        return nullptr;
    }

    T* Service = nullptr;
    ServiceLocator -> TryGetService(Service);
    return Service;
}
