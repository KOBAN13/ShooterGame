// Shoot Then Up Game, All Rights Reserved

#include "StructEventBusService.h"
#include "FCallbackWithPriorityStruct.h"

UStructEventBusService::UStructEventBusService()
{
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverStructHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>>();
}

void UStructEventBusService::Unsubscribe(const FName EventName)
{
    for (auto Receiver : EventReceiversStruct[EventName])
    {
        if (Receiver.IsValid())
        {
            EventReceiverStructHashToReference.Remove(Receiver -> GetHashCode());
            EventReceiversStruct.Remove(EventName);
        }
    }
}