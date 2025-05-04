// Shoot Then Up Game, All Rights Reserved


#include "ObjectEventBusService.h"

void UObjectEventBusService::Unsubscribe(const FName EventName)
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