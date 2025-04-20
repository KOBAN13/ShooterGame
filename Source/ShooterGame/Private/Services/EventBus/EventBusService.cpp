// Shoot Then Up Game, All Rights Reserved

#include "EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverObjectHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
    EventReceiverStructHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>>();
}