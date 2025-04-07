// Shoot Then Up Game, All Rights Reserved

#include "Services/EventBus/EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceivers = TMap<UObject*, TArray<TWeakObjectPtr<IBaseEventReceiver>>>();
    EventReceiverHashToReference = TMap<size_t, TWeakObjectPtr<IBaseEventReceiver>>();
}