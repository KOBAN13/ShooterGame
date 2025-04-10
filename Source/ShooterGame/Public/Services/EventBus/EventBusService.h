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
    
    DECLARE_DELEGATE(FGenericDelegate);
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

    TMap<FName, TArray<TWeakObjectPtr<FCallbackWithPriority>>> EventReceivers;
    TMap<size_t, TWeakObjectPtr<FCallbackWithPriority>> EventReceiverHashToReference;

    UEventBusService();

    template<typename TEvent = UObject>
    void AddEventReceiver(int32 priority, TFunction<void(TEvent)> Callback)
    {
        const FName EventName = TEvent::StaticClass() -> GetFName();
        
        if (!EventReceivers.Contains(EventName))
            EventReceivers[EventName] = TArray<TWeakObjectPtr<FCallbackWithPriority>>();

        auto* EventReceiver = new FCallbackWithPriority();
        EventReceiver -> Priority = priority;
        EventReceiver -> Delegate.BindLambda(Callback);
        
        const TWeakObjectPtr<FCallbackWithPriority> Receiver = TWeakObjectPtr(EventReceiver);

        EventReceivers[EventName].Add(Receiver);
        EventReceiverHashToReference.Add(EventReceiver -> GetHashCode(), Receiver);

        EventReceivers[EventName].Sort([](const TWeakObjectPtr<FCallbackWithPriority>& A, const TWeakObjectPtr<FCallbackWithPriority>& B)
        {
            A.Get() -> Priority > B.Get() -> Priority;
        });
    }

    template<typename TEvent = UObject>
    void RemoveEventReceiver(TFunction<void(TEvent)> Callback)
    {
        const FName EventName = TEvent::StaticClass() -> GetFName();

        if(!EventReceivers.Contains(EventName))
        {
            UE_LOG(LogTemp, Error, TEXT("Event %s not found"), *EventName.ToString());
            return;
        }
        
        const size_t Hash = EventReceivers[EventName]
        .FindByPredicate([Callback](const TWeakObjectPtr<FCallbackWithPriority>& Receiver)
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

                EventReceiver -> Delegate.Execute(EventObject);
            }
        }
    }
};
