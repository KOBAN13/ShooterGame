// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUGameInstance.h"
#include "UServiceManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServiceLocatorSubsystem.generated.h"

class UServiceManager;

template <typename T>
FORCEINLINE T* TryGetService(UWorld* World)
{
    if (World)
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World->GetGameInstance()))
        {
            T* Service = nullptr;
            UServiceLocatorSubsystem* ServiceLocator = GameInstance -> GetServiceLocator();
            ServiceLocator -> TryGetService(Service);
            return Service;
        }
    }
    return nullptr;
}

UCLASS()
class SHOOTERGAME_API UServiceLocatorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
    
    TWeakObjectPtr<UServiceManager> ServiceManager;

public:
    template <typename T = UObject>
    bool TryGetService(T*& OutService) const
    {
        return ServiceManager -> TryGetService(OutService);
    }

    template <typename T = UClass>
    void RegisterService(TSubclassOf<T> ServiceClass) const
    {
        ServiceManager -> RegisterService(ServiceClass);
    }

    template <typename T = UClass>
    void UnregisterService(OnServiceUnregistered OnServiceUnregistered = {}) const
    {
        ServiceManager -> UnregisterService(OnServiceUnregistered);
    }

    virtual void Deinitialize() override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
    UServiceManager* GetServiceManager() const { return ServiceManager.Get(); }
};
