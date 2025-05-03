// Shoot Then Up Game, All Rights Reserved


#include "ObjectEventBusService.h"

UObjectEventBusService::UObjectEventBusService()
{
    EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiverObjectHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
}

void UObjectEventBusService::Subscribe(const FName EventName, const int32 Priority, const TFunction<void(void*)>& Callback)
{
    AddReceiver(EventName, Priority, Callback);
}

void UObjectEventBusService::Unsubscribe(const FName EventName)
{
    for (auto Receiver : EventReceiversObject[EventName])
    {
        if (Receiver.IsValid())
        {
            EventReceiverObjectHashToReference.Remove(Receiver->GetHashCode());
            EventReceiversObject.Remove(EventName);
        }
    }
}

void UObjectEventBusService::SendEvent(const FName EventName, void* EventObject, UScriptStruct* StructType)
{
    UObject* EventObjectCast = nullptr;
    
    if (!EventReceiversObject.Contains(EventName))
        return;

    if(EventObjectCast != nullptr)
    {
        EventObjectCast = Cast<UObject>(EventObject);

        if(EventObjectCast == nullptr)
            return;
    }
    
    for (const auto& Receiver : EventReceiversObject[EventName])
    {
        if (Receiver.IsValid())
        {
            Receiver -> OneParamDelegate.ExecuteIfBound(EventObjectCast);
        }
    }
}