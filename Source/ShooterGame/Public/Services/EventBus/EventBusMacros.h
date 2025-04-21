// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventBusService.h"
#include "EventBusMacros.generated.h"

#define SUBSCRIBE_EVENT(EventName, Priority, Callback) \
    if(UEventBusService* EventBusService = UEventBusService::GetInstance()) \
       EventBusService -> Subscribe(EventName, Priority, Callback); \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SUBSCRIBE_OBJECT_EVENT(EventName, Priority, ObjectType, Callback) \
    if(UEventBusService* EventBusService = UEventBusService::GetInstance()) \
       EventBusService -> Subscribe<ObjectType>(EventName, Priority, Callback); \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SUBSCRIBE_STRUCT_EVENT(EventName, Priority, StructType, Callback) \
    if(UEventBusService* EventBusService = UEventBusService::GetInstance()) \
       EventBusService -> SubscribeStruct<StructType>(EventName, Priority, Callback); \
    else \
       UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SEND_EVENT(EventName) \
    if (UEventBusService* EventBusService = UEventBusService::GetInstance()) \
        EventBusService -> SendEvent(EventName); \
    else \
        UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SEND_EVENT_OBJECT(EventName, ObjectType, EventObject) \
    if (UEventBusService* EventBusService = UEventBusService::GetInstance()) \
        EventBusService -> SendEvent<ObjectType>(EventName, EventObject); \
    else \
        UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define SEND_EVENT_STRUCT(EventName, StructType, EventObject) \
    if (UEventBusService* EventBusService = UEventBusService::GetInstance()) \
        EventBusService -> SendEventStruct<StructType>(EventName, EventObject); \
    else \
        UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

#define UNSUBSCRIBE_EVENT(EventName) \
    if(UEventBusService* EventBusService = UEventBusService::GetInstance()) \
    EventBusService -> Unsubscribe(EventName) \
    else \
    UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \
    
#define UNSUBSCRIBE_EVENT_STRUCT(EventName) \
    if(UEventBusService* EventBusService = UEventBusService::GetInstance()) \
    EventBusService -> UnsubscribeStruct(EventName) \
    else \
    UE_LOG(LogTemp, Error, TEXT("EventBus not initialized!")) \

class UEventBusService;
UCLASS()
class SHOOTERGAME_API UEventBusMacros : public UObject
{
	GENERATED_BODY()
};
