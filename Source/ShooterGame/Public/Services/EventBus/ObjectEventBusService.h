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

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>> EventReceiversObject;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>> EventReceiverObjectHashToReference;
    
    UObjectEventBusService();

    
public:
    virtual void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(void*)>& Callback
    ) override;
    
    virtual void Unsubscribe(const FName EventName) override;
    
    virtual void SendEvent(
        const FName EventName,
        void* EventObject
    ) override;


    template<typename TEvent = void, typename TCallback>
    void AddReceiver(
        const FName EventName,
        const int32 Priority,
        const TCallback& Callback
    )
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
};
