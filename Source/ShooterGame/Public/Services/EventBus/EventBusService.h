// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventBusService.generated.h"

class IEventReceiver;
class IEventInterface;
class IBaseEventReceiver;

USTRUCT()
struct FCallbackWithPriority
{
    GENERATED_USTRUCT_BODY()
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

    virtual ~FCallbackWithPriority() = default;
};

UCLASS()
class SHOOTERGAME_API UEventBusService : public UObject
{
    GENERATED_BODY()

    TMap<FName, TArray<TSharedPtr<FCallbackWithPriority>>> EventReceivers;
    TMap<size_t, TSharedPtr<FCallbackWithPriority>> EventReceiverHashToReference;

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
    
    template<typename TEvent>
    void Unsubscribe(const FName EventName, const TFunction<void(TEvent*)>& Callback)
    {
        if(!EventReceivers.Contains(EventName))
        {
            UE_LOG(LogTemp, Error, TEXT("Event %s not found"), *EventName.ToString());
            return;
        }
        
        const void* CallbackUObject = Callback.GetUObject();
        const FName CallbackFunctionName = Callback.GetFunctionName();
        
        EventReceivers[EventName].RemoveAllSwap(
            [CallbackUObject, CallbackFunctionName](const TSharedPtr<FCallbackWithPriority>& Receiver)
            {
                return Receiver->OneParamDelegate.GetUObject() == CallbackUObject;
            },
            false
        );
    }
    
    template<typename TEvent>
    void SendEvent(const FName EventName, TEvent* EventObject)
    {
        if(!EventReceivers.Contains(EventName))
            return;
        
        for(const auto& Receiver : EventReceivers[EventName])
        {
            if(Receiver.IsValid())
            {
                if(EventObject)
                {
                    Receiver->OneParamDelegate.ExecuteIfBound(EventObject);
                }
            }
        }
    }
    
    void SendEvent(const FName EventName)
    {
        if(!EventReceivers.Contains(EventName))
            return;
        
        for(const auto& Receiver : EventReceivers[EventName])
        {
            if(Receiver.IsValid())
            {
                Receiver->SimpleDelegate.ExecuteIfBound();
            }
        }
    }

private:
    template<typename TEvent, typename TCallback>
    void ConvertAndBind(const TCallback& Callback, const TSharedPtr<FCallbackWithPriority> EventReceiver)
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
        TArray<TSharedPtr<FCallbackWithPriority>>& Receivers = EventReceivers.FindOrAdd(EventName);

        const TSharedPtr<FCallbackWithPriority> EventReceiver = MakeShared<FCallbackWithPriority>();
        EventReceiver->Priority = Priority;

        ConvertAndBind<TEvent>(Callback, EventReceiver);

        Receivers.Add(EventReceiver);
        EventReceiverHashToReference.Add(EventReceiver->GetHashCode(), EventReceiver);

        Receivers.Sort([](const TSharedPtr<FCallbackWithPriority>& A,
                        const TSharedPtr<FCallbackWithPriority>& B)
        {
            return A->Priority > B->Priority;
        });
    }
};
