// Shoot Then Up Game, All Rights Reserved

#include "Services/STUGameInstance.h"

UServiceLocatorSubsystem* USTUGameInstance::GetServiceLocatorSubsystem() const
{
    return GetSubsystem<UServiceLocatorSubsystem>();
}