// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventBusService.h"
#include "EventBusMacros.generated.h"

#define SUBSCRIBE_EVENT(EventName, Priority, Callback) \
UEventBusMacros::Get()->Subscribe(EventName, Priority, Callback)

#define SUBSCRIBE_OBJECT_EVENT(EventName, Priority, ObjectType, Callback) \
UEventBusMacros::Get()->Subscribe<ObjectType>(EventName, Priority, [](ObjectType* Obj) { Callback(Obj); })

#define SUBSCRIBE_STRUCT_EVENT(EventName, Priority, StructType, Callback) \
UEventBusMacros::Get()->SubscribeStruct<StructType>(EventName, Priority, [](const StructType* Struct) { Callback(Struct); })

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()

public:
    
    static UEventBusService* Get()
    {
        return GEngine->GetEngineSubsystem<UEventBusService>();
    }
};
