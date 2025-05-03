// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ObjectEventBusService.h"
#include "ServiceLocatorHelper.h"
#include "EventBusMacros.generated.h"

class UEventBusService;

FORCEINLINE void Subscribe(
    const FName EventName,
    const int32 Priority,
    const TFunction<void(void*)>& Callback,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UObjectEventBusService>(World))
    {
        EventBus -> Subscribe(EventName, Priority, Callback);
    }
};

FORCEINLINE void Unsubscribe(const FName EventName, UWorld* World)
{
    if (auto* EventBus = TryGetService<UObjectEventBusService>(World))
    {
        EventBus -> Unsubscribe(EventName);
    }
};

FORCEINLINE void SendEvent(
    const FName EventName,
    void* EventObject,
    UScriptStruct* StructType,
    UWorld* World
)
{
    if (auto* EventBus = TryGetService<UObjectEventBusService>(World))
    {
        EventBus -> SendEvent(EventName, EventObject, StructType);
    }
};

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()
};
