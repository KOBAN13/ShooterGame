// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventBusService.h"
#include "EventBusMacros.generated.h"

#define SUBSCRIBE_EVENT(EventName, Priority, Callback) \
    if(UEventBusService* EventBusService = UEventBusMacros::GetInstance()) \
       EventBusService -> Subscribe<void>(EventName, Priority, Callback); \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SUBSCRIBE_OBJECT_EVENT(EventName, Priority, ObjectType, Callback) \
    if(UEventBusService* EventBusService = UEventBusMacros::GetInstance()) \
       UEventBusService->Subscribe<ObjectType>(EventName, Priority, [](ObjectType* Obj) { Callback(Obj); }) \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SUBSCRIBE_STRUCT_EVENT(EventName, Priority, StructType, Callback) \
    if(UEventBusService* EventBusService = UEventBusMacros::GetInstance()) \
       UEventBusService->SubscribeStruct<StructType>(EventName, Priority, [](StructType* Struct) { Callback(Struct); }) \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \
       
#define UNSUBSCRIBE_EVENT(EventName) \
UEventBusMacros::Get()->Unsubscribe(EventName)

#define UNSUBSCRIBE_EVENT_STRUCT(EventName) \
UEventBusMacros::Get()->UnsubscribeStruct(EventName)

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()

public:
    static UEventBusService* Get()
    {
        return GEngine -> GetEngineSubsystem<UEventBusService>();
    }
};
