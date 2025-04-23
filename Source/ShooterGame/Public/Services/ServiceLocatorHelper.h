#pragma once

#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"

template <typename T>
FORCEINLINE T* TryGetService(UWorld* World)
{
    if (World)
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World->GetGameInstance()))
        {
            T* Service = nullptr;
            UServiceLocatorSubsystem* ServiceLocator = GameInstance -> GetServiceLocator();
            ServiceLocator -> TryGetService(Service);
            return Service;
        }
    }
    return nullptr;
}
