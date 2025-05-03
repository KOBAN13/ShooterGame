// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ObjectEventBusService.h"
#include "ServiceLocatorHelper.h"
#include "ServiceLocatorSubsystem.h"
#include "EventBusMacros.generated.h"

class UEventBusService;

template<typename TEvent, typename TEventBus = UBaseEventBus>
FORCEINLINE void Subscribe(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(TEvent*)>& Callback,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<TEventBus>(World))
    {
        EventBus -> Subscribe(EventName, Priority, Callback);
    }
}

template<typename T = UBaseEventBus>
FORCEINLINE void Unsubscribe(const FName EventName, UWorld* World)
{
    if (auto* EventBus = TryGetService<T>(World))
    {
        EventBus -> Unsubscribe(EventName);
    }
}

template<typename TEvent, typename TEventBus = UBaseEventBus>
FORCEINLINE void SendEvent(
    const FName EventName,
    UWorld* World,
    const TEvent* EventObject = nullptr
)
{
    if (auto* EventBus = TryGetService<TEventBus>(World))
    {
        EventBus -> SendEvent(EventName, EventObject);
    }
}

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()
};
