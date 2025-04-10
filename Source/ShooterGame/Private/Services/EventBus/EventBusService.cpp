// Shoot Then Up Game, All Rights Reserved

#include "Services/EventBus/EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceivers = TMap<FName, TArray<TWeakObjectPtr<FCallbackWithPriority>>>();
    EventReceiverHashToReference = TMap<size_t, TWeakObjectPtr<FCallbackWithPriority>>();
}