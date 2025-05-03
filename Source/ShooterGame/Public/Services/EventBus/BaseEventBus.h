// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "FCallbackWithPriorityObject.h"
#include "BaseEventBus.generated.h"

UCLASS(Abstract)
class SHOOTERGAME_API UBaseEventBus : public UObject
{
	GENERATED_BODY()

public:
    virtual void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(void*)>& Callback
     );
    
    virtual void Unsubscribe(const FName EventName);
    
    virtual void SendEvent(
        const FName EventName,
        void* EventObject = nullptr
    );
    
    template<typename TEvent, typename TCallback>
    void ConvertAndBind(const TCallback& Callback, const TSharedPtr<FCallbackWithPriorityObject> EventReceiver)
    {
        if constexpr(std::is_same_v<TEvent, void>)
        {
            EventReceiver->SimpleDelegate.BindLambda([Callback]() { Callback(); });
        }
        else
        {
            EventReceiver->OneParamDelegate.BindLambda([Callback](UObject* Obj)
            {
                if(TEvent* TypedObj = Cast<TEvent>(Obj))
                {
                    Callback(TypedObj);
                }
            });
        }
    }
};
