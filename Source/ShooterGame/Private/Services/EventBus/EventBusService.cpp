// Shoot Then Up Game, All Rights Reserved

#include "EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceivers = TMap<FName, TArray<TSharedPtr<FCallbackWithPriority>>>();
    EventReceiverHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriority>>();
}