// Shoot Then Up Game, All Rights Reserved

#include "Services/STUGameInstance.h"
#include "Services/ServiceLocatorSubsystem.h"

UServiceLocatorSubsystem* USTUGameInstance::GetServiceLocatorSubsystem() const
{
    return GetSubsystem<UServiceLocatorSubsystem>();
}