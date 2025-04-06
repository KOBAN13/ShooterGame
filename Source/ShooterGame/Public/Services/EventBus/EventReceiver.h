// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventReceiver.h"
#include "UObject/Interface.h"
#include "EventReceiver.generated.h"

class IEventInterface;

UINTERFACE(MinimalAPI)
class UEventReceiver : public IBaseEventReceiver
{
	GENERATED_BODY()
};

class SHOOTERGAME_API IEventReceiver : public IBaseEventReceiver
{
	GENERATED_BODY()

public:
    void OnEvent(UObject* EventObject);

    template<typename T = IEventInterface> 
    void OnEventTyped(T* Event)
    {
        OnEvent(Cast<UObject>(Event));
    }
};
