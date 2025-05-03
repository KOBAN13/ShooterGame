// Shoot Then Up Game, All Rights Reserved

#include "VoidEventBusService.h"

UVoidEventBusService::UVoidEventBusService()
{
    EventReceiversVoid = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiverVoidHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
}

void UVoidEventBusService::Subscribe(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(void*)>& Callback
)
{
    AddReceiver<void>(EventName, Priority, Callback);
}

void UVoidEventBusService::Unsubscribe(const FName EventName)
{
    for (auto Receiver : EventReceiversVoid[EventName])
    {
        if (Receiver.IsValid())
        {
            EventReceiverVoidHashToReference.Remove(Receiver -> GetHashCode());
            EventReceiversVoid.Remove(EventName);
        }
    }
}

void UVoidEventBusService::SendEvent(
    const FName EventName,
    void* EventObject,
    UScriptStruct* StructType
)
{
    if (!EventReceiversVoid.Contains(EventName))
        return;

    for (const auto& Receiver : EventReceiversVoid[EventName])
    {
        if (Receiver.IsValid())
        {
            Receiver->SimpleDelegate.ExecuteIfBound();
        }
    }
}