// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventReceiver.h"
#include "EventReceiver.generated.h"

class IEventInterface;

UINTERFACE(MinimalAPI)
class UEventReceiver : public UBaseEventReceiver
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IEventReceiver : public IBaseEventReceiver
{
	GENERATED_BODY()

public:
    virtual void OnEvent(UObject* EventObject) = 0;

    template<typename T = IEventInterface> 
    void OnEventTyped(T* Event)
    {
        if(UObject* Object = Cast<T>(Event))
        {
            OnEvent(Object);
        }
    }

    virtual size_t GetHashCode() const
    {
        if(!this) return 0;
        
        if (const UObject* Object = Cast<UObject>(this))
        {
            return GetTypeHash(Object);
        }
        
        return reinterpret_cast<size_t>(this);
    }
};
