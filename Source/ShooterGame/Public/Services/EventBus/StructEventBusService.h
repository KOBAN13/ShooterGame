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
