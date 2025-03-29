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
    bool TryGetService(T*& OutService) const;

    template <typename T = UClass>
    void RegisterService(TSubclassOf<T> ServiceClass) const;

    template <typename T = UClass>
    void UnregisterService(T* ServiceClass, OnServiceUnregistered OnServiceUnregistered = {}) const;

    virtual void Deinitialize() override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    
    UServiceManager* GetServiceManager() const { return ServiceManager.Get(); }
};
