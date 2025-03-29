// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UServiceManager.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ServiceLocatorSubsystem.generated.h"

class UServiceManager;
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
