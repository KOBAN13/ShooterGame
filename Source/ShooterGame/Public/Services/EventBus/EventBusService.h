// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EventReceiver.h"
#include "EventInterface.h"
#include "EventBusService.generated.h"

class IEventReceiver;
class IEventInterface;
class IBaseEventReceiver;

UCLASS()
class SHOOTERGAME_API UEventBusService : public UObject
{
    GENERATED_BODY()

    TMap<TWeakObjectPtr<>, TArray<TWeakObjectPtr<>>> EventReceivers;
    TMap<size_t, TWeakObjectPtr<>> EventReceiverHashToReference;

    UEventBusService();
    
    void AddEventReceiver(IEventReceiver* EventReceiver)
    {
        UObject* Object = Cast<UObject>(EventReceiver);
        
        if (!EventReceivers.Contains(Object))
            EventReceivers[Object] = TArray<TWeakObjectPtr<>>();

        const TWeakObjectPtr<> Reference = TWeakObjectPtr<>(Object);

        EventReceivers[Object].Add(Reference);
        EventReceiverHashToReference.Add(EventReceiver -> GetHashCode(), Reference);
    }

    void RemoveEventReceiver(IEventReceiver* EventReceiver)
    {
        const UObject* Object = Cast<UObject>(EventReceiver);
        const size_t Hash = EventReceiver -> GetHashCode();

        if(!EventReceivers.Contains(Object) || !EventReceiverHashToReference.Contains(Hash))
            return;
        
        auto const Reference = EventReceiverHashToReference[Hash];

        EventReceivers[Object].Remove(Reference);
        EventReceiverHashToReference.Remove(Hash);
    }

    void SendEvent(IEventInterface* EventObject)
    {
        const UObject* Object = Cast<UObject>(EventObject);

        if(!EventReceivers.Contains(Object))
            return;
        
        for(const auto& Receiver : EventReceivers[Object])
        {
            if(Receiver.IsValid())
            {
                auto* EventReceiver = Receiver.Get();

                if(IEventReceiver* CastedReceiver = Cast<IEventReceiver>(EventReceiver))
                {
                    CastedReceiver -> OnEventTyped(EventObject);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("EventReceiver is not IEventReceiver"));
                }
            }
        }
    }
};
