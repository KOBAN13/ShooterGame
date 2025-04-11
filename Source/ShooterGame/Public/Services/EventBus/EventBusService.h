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
    GENERATED_BODY()
    int32 Priority;
    
    DECLARE_DELEGATE_OneParam(FGenericDelegate, UObject*);
    FGenericDelegate Delegate;

    virtual size_t GetHashCode() const
    {
        size_t Hash = GetTypeHash(Priority);

        if (Delegate.IsBound())
        {
            Hash = HashCombine(Hash, GetTypeHash(Delegate.GetUObject()));
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
    template<typename TEvent = UObject>
    void Subscribe(const int32 Priority, const TFunction<void(TEvent*)>& Callback)
    {
        const FName EventName = TEvent::StaticClass() -> GetFName();
        
        if (!EventReceivers.Contains(EventName))
            EventReceivers[EventName] = TArray<TSharedPtr<FCallbackWithPriority>>();

        auto* EventReceiver = new FCallbackWithPriority();
        EventReceiver -> Priority = Priority;

        auto WrapperLambda = [Callback](UObject* Obj) //в метод и разобратся
        {
            if (TEvent* TypedObj = Cast<TEvent>(Obj))
            {
                Callback(TypedObj);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Type mismatch in delegate callback!"));
            }
        };
        
        EventReceiver -> Delegate.BindLambda(WrapperLambda);

        const TSharedPtr<FCallbackWithPriority> Receiver =
            MakeShared<FCallbackWithPriority>();

        EventReceivers[EventName].Add(Receiver);
        EventReceiverHashToReference.Add(EventReceiver -> GetHashCode(), Receiver);

        EventReceivers[EventName].Sort([](const TSharedPtr<FCallbackWithPriority>& A,
            const TSharedPtr<FCallbackWithPriority>& B)
        {
            return A.Get() -> Priority > B.Get() -> Priority;
        });
    }

    template<typename TEvent = UObject>
    void Unsubscribe(const TFunction<void(TEvent*)>& Callback)
    {
        const FName EventName = TEvent::StaticClass() -> GetFName();

        if(!EventReceivers.Contains(EventName))
        {
            UE_LOG(LogTemp, Error, TEXT("Event %s not found"), *EventName.ToString());
            return;
        }
        
        const size_t Hash = EventReceivers[EventName]
        .FindByPredicate([Callback](const TSharedPtr<FCallbackWithPriority>& Receiver)
        -> bool
        {
            return Receiver.Get() -> Delegate.GetUObject() == Callback.GetUObject();
        });
        
        auto const Reference = EventReceiverHashToReference[Hash];

        EventReceivers[EventName].Remove(Reference);
        EventReceiverHashToReference.Remove(Hash);
    }

    template<typename TEvent = UObject>
    void SendEvent(TEvent EventObject)
    {
        const FName EventName = EventObject -> GetFName();

        if(!EventReceivers.Contains(EventName))
            return;
        
        for(const auto& Receiver : EventReceivers[EventName])
        {
            if(Receiver.IsValid())
            {
                auto* EventReceiver = Receiver.Get();

                if(!EventReceiver -> Delegate.IsBound())
                    continue;

                if(auto* Object = Cast<UObject>(EventObject))
                {
                    EventReceiver -> Delegate.ExecuteIfBound(Object);
                }
            }
        }
    }
};
