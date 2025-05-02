// Shoot Then Up Game, All Rights Reserved


#include "StructEventBusService.h"

UStructEventBusService::UStructEventBusService()
{
    EventReceiversStruct = TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>>();
    EventReceiverStructHashToReference = TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>>();
}