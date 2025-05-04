// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.h"
#include "FCallbackWithPriorityStruct.h"
#include "StructEventBusService.generated.h"

struct FCallbackWithPriorityStruct;

UCLASS()
class SHOOTERGAME_API UStructEventBusService : public UBaseEventBus
{
	GENERATED_BODY()
    
    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>> EventReceiversStruct;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>> EventReceiverStructHashToReference;

    UStructEventBusService();

public:
    template<typename TStruct>
    void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(TStruct*)>& Callback
    )
    {
        AddReceiverStruct<TStruct>(EventName, Priority, Callback);
    }
    
    virtual void Unsubscribe(const FName EventName);

    template<typename TStruct>
    void SendEvent(
        const FName EventName,
        TStruct* EventObject
    )
    {
        if(!EventReceiversStruct.Contains(EventName))
            return;

        UScriptStruct* StructType = TStruct::StaticStruct();
        void* Data = static_cast<void*>(EventObject);

        for(const auto& Receiver : EventReceiversStruct[EventName])
        {
            if(Receiver.IsValid())
            {
                Receiver->StructDelegate.ExecuteIfBound(StructType, Data);
            }
        }
    }

    
    template<typename TStruct>
    void AddReceiverStruct(const FName EventName, const int32 Priority, const TFunction<void(TStruct*)>& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityStruct>>& Receivers = EventReceiversStruct.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityStruct> EventReceiver = MakeShared<FCallbackWithPriorityStruct>();

        EventReceiver -> Priority = Priority;
        EventReceiver -> StructDelegate.BindLambda([Callback](UScriptStruct* StructType, void* Data)
        {
            if(StructType == TStruct::StaticStruct())
            {
                Callback(static_cast<TStruct*>(Data));
            }
        });

        Receivers.Add(EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityStruct>& A,
                const TSharedPtr<FCallbackWithPriorityStruct>& B)
                {
                    return A -> Priority > B -> Priority;
                });

        EventReceiverStructHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);
    }
};
