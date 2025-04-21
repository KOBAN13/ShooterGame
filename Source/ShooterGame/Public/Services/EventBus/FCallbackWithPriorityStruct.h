#pragma once

#include "CoreMinimal.h"
#include "FCallbackWithPriorityStruct.generated.h"

USTRUCT()
struct FCallbackWithPriorityStruct
{
    GENERATED_BODY()
    int32 Priority = 0;

    DECLARE_DELEGATE_TwoParams(FGenericStructDelegate, UScriptStruct*, void*);
    FGenericStructDelegate StructDelegate;

    virtual size_t GetHashCode() const
    {
        size_t Hash = GetTypeHash(Priority);

        if (StructDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(StructDelegate.GetUObject()));
        }

        return Hash;
    }
    virtual ~FCallbackWithPriorityStruct() = default;
};
