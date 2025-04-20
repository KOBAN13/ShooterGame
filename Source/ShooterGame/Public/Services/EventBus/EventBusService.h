// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventBusService.generated.h"

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
        
        if(StructDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(StructDelegate.GetUObject()));
        }
        
        return Hash;
    }
    virtual ~FCallbackWithPriorityStruct() = default;
};

USTRUCT()
struct FCallbackWithPriorityObject
{
    GENERATED_BODY()
    int32 Priority;
    
    DECLARE_DELEGATE_OneParam(FGenericDelegateOneParam, UObject*);
    FGenericDelegateOneParam OneParamDelegate;

    DECLARE_DELEGATE(FGenericDelegate);
    FGenericDelegate SimpleDelegate;

    virtual size_t GetHashCode() const
    {
        size_t Hash = GetTypeHash(Priority);

        if (SimpleDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(SimpleDelegate.GetUObject()));
        }

        if(OneParamDelegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(OneParamDelegate.GetUObject()));
        }
        
        return Hash;
    }
    
    
    virtual ~FCallbackWithPriorityObject() = default;
};

UCLASS()
class SHOOTERGAME_API UEventBusService : public UObject
{
    GENERATED_BODY()

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityObject>>> EventReceiversObject;
    TMap<FName, TArray<TSharedPtr<FCallbackWithPriorityStruct>>> EventReceiversStruct;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityObject>> EventReceiverObjectHashToReference;
    TMap<size_t, TSharedPtr<FCallbackWithPriorityStruct>> EventReceiverStructHashToReference;

    UEventBusService();

    public:
    template<typename TEvent>
    void Subscribe(const FName EventName, const int32 Priority, const TFunction<void(TEvent*)>& Callback)
    {
        AddReceiver<TEvent>(EventName, Priority, Callback);
    }
    
    void Subscribe(const FName EventName, const int32 Priority, const TFunction<void()>& Callback)
    {
        AddReceiver<void>(EventName, Priority, Callback);
    }
    
    template<typename TStruct>
    void SubscribeStruct(const FName EventName, const int32 Priority, const TFunction<void(TStruct*)>& Callback)
    {
        AddReceiverStruct<TStruct>(EventName, Priority, Callback);
    }
    
    void Unsubscribe(const FName EventName)
    {
        for (auto Receiver : EventReceiversObject[EventName])
        {
            if (Receiver.IsValid())
            {
                EventReceiverObjectHashToReference.Remove(Receiver->GetHashCode());
                EventReceiversObject.Remove(EventName);
            }
        }
    }
    
    void UnsubscribeStruct(const FName EventName)
    {
        for (auto Receiver : EventReceiversStruct[EventName])
        {
            if (Receiver.IsValid())
            {
                EventReceiverStructHashToReference.Remove(Receiver->GetHashCode());
                EventReceiversStruct.Remove(EventName);
            }
        }
    }

    template<typename TStruct>
    void SendEventStruct(const FName EventName, TStruct* EventObject)
    {
        if(!EventReceiversStruct.Contains(EventName))
            return;

        UScriptStruct* StructType = TStruct::StaticStruct();
        void* Data = static_cast<void*>(EventObject);

        for(const auto& Receiver : EventReceiversStruct[EventName])
        {
            if(Receiver.IsValid())
            {
                Receiver->StructDelegate.ExecuteIfBound(StructType, Data);
            }
        }
    }
    
    template<typename TEvent>
    void SendEvent(const FName EventName, TEvent* EventObject)
    {
        if (!EventReceiversObject.Contains(EventName))
            return;
    
        for (const auto& Receiver : EventReceiversObject[EventName])
        {
            if (Receiver.IsValid())
            {
                Receiver -> OneParamDelegate.ExecuteIfBound(EventObject);
            }
        }
    }
    
    void SendEvent(const FName EventName)
    {
        if (!EventReceiversObject.Contains(EventName))
            return;

        for (const auto& Receiver : EventReceiversObject[EventName])
        {
            if (Receiver.IsValid())
            {
                Receiver->SimpleDelegate.ExecuteIfBound();
            }
        }
    }

private:
    template<typename TEvent, typename TCallback>
    void ConvertAndBind(const TCallback& Callback, const TSharedPtr<FCallbackWithPriorityObject> EventReceiver)
    {
        if constexpr(std::is_same_v<TEvent, void>)
        {
            EventReceiver->SimpleDelegate.BindLambda([Callback]() { Callback(); });
        }
        else
        {
            EventReceiver->OneParamDelegate.BindLambda([Callback](UObject* Obj)
            {
                if(TEvent* TypedObj = Cast<TEvent>(Obj))
                {
                    Callback(TypedObj);
                }
            });
        }
    }

    template<typename TEvent = void, typename TCallback>
    void AddReceiver(const FName EventName, const int32 Priority, const TCallback& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityObject>>& Receivers = EventReceiversObject.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityObject> EventReceiver = MakeShared<FCallbackWithPriorityObject>();
        EventReceiver -> Priority = Priority;

        ConvertAndBind<TEvent>(Callback, EventReceiver);

        Receivers.Add(EventReceiver);
        EventReceiverObjectHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityObject>& A,
                        const TSharedPtr<FCallbackWithPriorityObject>& B)
        {
            return A -> Priority > B -> Priority;
        });
    }

    template<typename TStruct>
    void AddReceiverStruct(const FName EventName, const int32 Priority, const TFunction<void(TStruct*)>& Callback)
    {
        TArray<TSharedPtr<FCallbackWithPriorityStruct>>& Receivers = EventReceiversStruct.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriorityStruct> EventReceiver = MakeShared<FCallbackWithPriorityStruct>();

        EventReceiver -> Priority = Priority;
        EventReceiver -> StructDelegate.BindLambda([Callback](UScriptStruct* StructType, void* Data)
        {
            if(StructType == TStruct::StaticStruct())
            {
                Callback(static_cast<TStruct*>(Data));
            }
        });

        Receivers.Add(EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriorityStruct>& A,
                const TSharedPtr<FCallbackWithPriorityStruct>& B)
                {
                    return A -> Priority > B -> Priority;
                });

        EventReceiverStructHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);
    }
};
