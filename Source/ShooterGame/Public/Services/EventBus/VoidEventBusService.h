// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.h"
#include "FCallbackWithPriorityObject.h"
#include "VoidEventBusService.generated.h"

struct FCallbackWithPriorityObject;

UCLASS()
class SHOOTERGAME_API UVoidEventBusService : public UBaseEventBus
{
	GENERATED_BODY()

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>> EventReceiversVoid;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>> EventReceiverVoidHashToReference;
    
    UVoidEventBusService();

public:
    virtual void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(void*)>& Callback
    ) override;
    
    virtual void Unsubscribe(const FName EventName) override;
    
    virtual void SendEvent(
        const FName EventName,
        void* EventObject,
        UScriptStruct* StructType
    ) override;


    template<typename TEvent = void, typename TCallback>
    void AddReceiver(const FName EventName, const int32 Priority, const TCallback& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityObject>>& Receivers = EventReceiversVoid.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityObject> EventReceiver = MakeShared<FCallbackWithPriorityObject>();
        EventReceiver -> Priority = Priority;

        ConvertAndBind<TEvent>(Callback, EventReceiver);

        Receivers.Add(EventReceiver);
        EventReceiverVoidHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityObject>& A,
                        const TSharedPtr<FCallbackWithPriorityObject>& B)
        {
            return A -> Priority > B -> Priority;
        });
    }
};
