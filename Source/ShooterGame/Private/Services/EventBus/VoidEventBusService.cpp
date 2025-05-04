// Shoot Then Up Game, All Rights Reserved

#include "VoidEventBusService.h"
#include "FCallbackWithPriorityVoid.h"

void UVoidEventBusService::Subscribe(
    const FName EventName,
    const int32 Priority,
    const TFunction<void()>& Callback
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
            EventReceiverVoidHashToReference.Remove(Receiver->GetHashCode());
            EventReceiversVoid.Remove(EventName);
        }
    }
}

void UVoidEventBusService::SendEvent(const FName EventName)
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