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

template <typename T>
bool UServiceLocatorSubsystem::TryGetService(T*& OutService) const
{
    return ServiceManager -> TryGetService(OutService);
}

template <typename T>
void UServiceLocatorSubsystem::RegisterService(TSubclassOf<T> ServiceClass) const
{
    ServiceManager -> RegisterService(ServiceClass);
}

template <typename T>
void UServiceLocatorSubsystem::UnregisterService(T* ServiceClass, OnServiceUnregistered OnServiceUnregistered) const
{
    ServiceManager -> UnregisterService(ServiceClass, OnServiceUnregistered);
}