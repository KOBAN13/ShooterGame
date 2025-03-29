// Shoot Then Up Game, All Rights Reserved

#include "Services/ServiceLocatorSubsystem.h"
#include "UServiceManager.h"

void UServiceLocatorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    ServiceManager = NewObject<UServiceManager>();
    UE_LOG(LogTemp, Warning, TEXT("ServiceLocatorSubsystem initialized"));
}

void UServiceLocatorSubsystem::Deinitialize()
{
    Super::Deinitialize();

    ServiceManager -> Deinitialize();
    ServiceManager = nullptr;
}