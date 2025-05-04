#pragma once

#include "CoreMinimal.h"
#include "FCallbackWithPriorityVoid.generated.h"

USTRUCT()
struct FCallbackWithPriorityVoid
{
    GENERATED_BODY()
    int32 Priority;
    
    DECLARE_DELEGATE(FGenericDelegate);
    FGenericDelegate SimpleDelegate;

    virtual size_t GetHashCode() const
    {
        size_t Hash = GetTypeHash(Priority);

        if (SimpleDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(SimpleDelegate.GetUObject()));
        }
        
        return Hash;
    }
    
    virtual ~FCallbackWithPriorityVoid() = default;
};
