// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BaseEventBus.h"
#include "StructEventBusService.generated.h"

struct FCallbackWithPriorityStruct;

UCLASS()
class SHOOTERGAME_API UStructEventBusService : public UBaseEventBus
{
	GENERATED_BODY()
    
    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>> EventReceiversStruct;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>> EventReceiverStructHashToReference;

    UStructEventBusService();
};
