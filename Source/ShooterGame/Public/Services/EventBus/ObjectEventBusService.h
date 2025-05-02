// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectEventBusService.generated.h"

struct FCallbackWithPriorityObject;

UCLASS()
class SHOOTERGAME_API UObjectEventBusService : public UObject
{
	GENERATED_BODY()

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>> EventReceiversObject;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>> EventReceiverObjectHashToReference;


    UObjectEventBusService();
};
