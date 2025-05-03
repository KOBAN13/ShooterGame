// Shoot Then Up Game, All Rights Reserved

#include "StructEventBusService.h"
#include "FCallbackWithPriorityStruct.h"

UStructEventBusService::UStructEventBusService()
{
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverStructHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>>();
}

void UStructEventBusService::Subscribe(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(void*)>& Callback
)
{
    AddReceiverStruct(EventName, Priority, Callback);
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

void UStructEventBusService::SendEvent(
    const FName EventName,
    void* EventObject,
    UScriptStruct* StructType
)
{
    if(!EventReceiversStruct.Contains(EventName))
        return;

    if(EventObject == nullptr || StructType == nullptr)
        return;

    for(const auto& Receiver : EventReceiversStruct[EventName])
    {
        if(Receiver.IsValid())
        {
            Receiver->StructDelegate.ExecuteIfBound(StructType, EventObject);
        }
    }
}