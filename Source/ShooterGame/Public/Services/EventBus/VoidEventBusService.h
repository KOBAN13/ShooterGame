// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.h"
#include "FCallbackWithPriorityVoid.h"
#include "VoidEventBusService.generated.h"

struct FCallbackWithPriorityVoid;

UCLASS()
class SHOOTERGAME_API UVoidEventBusService : public UBaseEventBus
{
	GENERATED_BODY()
    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityVoid>>> EventReceiversVoid = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityVoid>>>();
    TMap<size_t, TSharedPtr<FCallbackWithPriorityVoid>> EventReceiverVoidHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityVoid>>();

public:
    void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void()>& Callback
    );
    
    virtual void Unsubscribe(const FName EventName);
    
    virtual void SendEvent(const FName EventName);

private:
    template<typename TEvent = void, typename TCallback>
    void AddReceiver(const FName EventName, const int32 Priority, const TCallback& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityVoid>>& Receivers = EventReceiversVoid.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityVoid> EventReceiver = MakeShared<FCallbackWithPriorityVoid>();
        EventReceiver -> Priority = Priority;

        ConvertAndBind(Callback, EventReceiver);

        Receivers.Add(EventReceiver);
        EventReceiverVoidHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityVoid>& A,
                        const TSharedPtr<FCallbackWithPriorityVoid>& B)
        {
            return A -> Priority > B -> Priority;
        });
    }
    
    template<typename TCallback>
    static void ConvertAndBind(const TCallback& Callback, const TSharedPtr<FCallbackWithPriorityVoid> EventReceiver)
    {
        EventReceiver->SimpleDelegate.BindLambda([Callback]() { Callback(); });
    }
};
