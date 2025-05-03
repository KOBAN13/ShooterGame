// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.generated.h"

UCLASS()
class SHOOTERGAME_API UBaseEventBus : public UObject
{
	GENERATED_BODY()
    
    virtual void Subscribe(
        const FName EventName,
        const int32 Priority,
        const TFunction<void(void*)>& Callback
     );
    
    virtual void Unsubscribe(const FName EventName);
    
    virtual void SendEvent(
        const FName EventName,
        void* EventObject = nullptr,
        UScriptStruct* StructType = nullptr
    );
};
