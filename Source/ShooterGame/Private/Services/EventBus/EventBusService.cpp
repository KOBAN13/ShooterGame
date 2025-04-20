// Shoot Then Up Game, All Rights Reserved

#include "EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
}