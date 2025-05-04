// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.h"
#include "FCallbackWithPriorityObject.h"
#include "ObjectEventBusService.generated.h"

struct FCallbackWithPriorityObject;

UCLASS()
class SHOOTERGAME_API UObjectEventBusService : public UBaseEventBus
{
	GENERATED_BODY()

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>> EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>> EventReceiverObjectHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();

public:
    template<typename TEvent>
    void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(TEvent*)>& Callback
    )
	{
        AddReceiver<TEvent>(EventName, Priority, Callback);
	}
    
    void Unsubscribe(const FName EventName);

    template<typename TEvent>
    void SendEvent(
        const FName EventName,
        TEvent* EventObject
    )
	{
	    if (!EventReceiversObject.Contains(EventName))
	        return;
    
	    for (const auto& Receiver : EventReceiversObject[EventName])
	    {
	        if (Receiver.IsValid())
	        {
	            Receiver -> OneParamDelegate.ExecuteIfBound(EventObject);
	        }
	    }
	}

private:
    template<typename TEvent = void, typename TCallback>
    void AddReceiver(const FName EventName, const int32 Priority, const TCallback& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityObject>>& Receivers = EventReceiversObject.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityObject> EventReceiver = MakeShared<FCallbackWithPriorityObject>();
        EventReceiver -> Priority = Priority;

        ConvertAndBind<TEvent>(Callback, EventReceiver);

        Receivers.Add(EventReceiver);
        EventReceiverObjectHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityObject>& A,
                        const TSharedPtr<FCallbackWithPriorityObject>& B)
        {
            return A -> Priority > B -> Priority;
        });
    }

    template<typename TEvent, typename TCallback>
    void ConvertAndBind(const TCallback& Callback, const TSharedPtr<FCallbackWithPriorityObject> EventReceiver)
    {
        EventReceiver->OneParamDelegate.BindLambda([Callback](UObject* Obj)
        {
            if(TEvent* TypedObj = Cast<TEvent>(Obj))
            {
                Callback(TypedObj);
            }
        }
        );
    }
};
