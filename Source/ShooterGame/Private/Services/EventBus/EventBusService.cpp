// Shoot Then Up Game, All Rights Reserved

#include "EventBusService.h"

UEventBusService::UEventBusService()
{
    EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverObjectHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
    EventReceiverStructHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>>();
}

UEventBusService* UEventBusService::GetInstance()
{
    if(!Instance)
    {
        InitializeSingleton();
    }
    return Instance;
}

void UEventBusService::InitializeSingleton()
{
    if (!Instance)
    {
        Instance = NewObject<UEventBusService>();
        Instance -> AddToRoot(); 
    }
}

void UEventBusService::Shutdown()
{
    if (Instance)
    {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
}

void UEventBusService::BeginDestroy()
{
    Shutdown();
    Super::BeginDestroy();
}