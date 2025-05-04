#pragma once

#include "CoreMinimal.h"
#include "FCallbackWithPriorityObject.generated.h"

USTRUCT()
struct FCallbackWithPriorityObject
{
    GENERATED_BODY()
    int32 Priority;
    
    DECLARE_DELEGATE_OneParam(FGenericDelegateOneParam, UObject*);
    FGenericDelegateOneParam OneParamDelegate;

    virtual size_t GetHashCode() const
    {
        size_t Hash = GetTypeHash(Priority);

        if(OneParamDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(OneParamDelegate.GetUObject()));
        }
        
        return Hash;
    }
    
    virtual ~FCallbackWithPriorityObject() = default;
};