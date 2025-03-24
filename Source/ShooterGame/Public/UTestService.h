#pragma once

#include "CoreMinimal.h"
#include "UTestService.generated.h"

UCLASS()
class SHOOTERGAME_API UTestService : public UObject
{
    GENERATED_BODY()

public:
    static void WorkService();
    UTestService();
};
