// Shoot Then Up Game, All Rights Reserved


#include "ObjectEventBusService.h"

UObjectEventBusService::UObjectEventBusService()
{
    EventReceiversObject = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>>();
    EventReceiverObjectHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>>();
}