// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ObjectEventBusService.h"
#include "ServiceLocatorHelper.h"
#include "StructEventBusService.h"
#include "VoidEventBusService.h"
#include "EventBusMacros.generated.h"

class UVoidEventBusService;
class UObjectEventBusService;
class UStructEventBusService;
class UEventBusService;

FORCEINLINE void Subscribe_Void(
    const FName EventName,
    const int32 Priority,
    const TFunction<void()>& Callback,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UVoidEventBusService>(World))
    {
        EventBus -> Subscribe(EventName, Priority, Callback);
    }
}

template<typename TEvent>
FORCEINLINE void Subscribe_OneParamObject(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(TEvent*)>& Callback,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UObjectEventBusService>(World))
    {
        EventBus -> Subscribe(EventName, Priority, Callback);
    }
}

template<typename TEvent>
FORCEINLINE void Subscribe_OneParamStruct(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(TEvent*)>& Callback,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UStructEventBusService>(World))
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
FORCEINLINE void SendEvent_OneParam(
    const FName EventName,
    UWorld* World,
    TEvent* EventObject
)
{
    if (auto* EventBus = TryGetService<TEventBus>(World))
    {
        EventBus -> SendEvent(EventName, EventObject);
    }
}

FORCEINLINE void SendEvent_Void(
    const FName EventName,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UVoidEventBusService>(World))
    {
        EventBus -> SendEvent(EventName);
    }
}

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()
};
