// Shoot Then Up Game, All Rights Reserved

#include "Services/EventBus/EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceivers = TMap<TWeakObjectPtr<>, TArray<TWeakObjectPtr<>>>();
    EventReceiverHashToReference = TMap<size_t, TWeakObjectPtr<>>();
}