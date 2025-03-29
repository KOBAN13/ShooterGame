// Shoot Then Up Game, All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "UServiceManager.generated.h"

DECLARE_DELEGATE(OnServiceUnregistered);

UCLASS()
class SHOOTERGAME_API UServiceManager : public UObject
{
    GENERATED_BODY()
    
    TMap<UClass*, TWeakObjectPtr<>> Services;
    void InitializeFields();
    UServiceManager();

public:
    template <typename T = UObject>
    bool TryGetService(T*& OutService)
    {
        UClass* Class = T::StaticClass();
        TWeakObjectPtr<>* FindService = Services.Find(Class);

        if (FindService && FindService->IsValid())
        {
            OutService = Cast<T>(FindService->Get());
            return true;
        }

        OutService = nullptr;
        return false;
    }

    template <typename T = UClass>
    void RegisterService(TSubclassOf<T> ServiceClass)
    {
        if(ServiceClass == nullptr)
            return;
        
        UClass* Class = ServiceClass.Get();

        if (Services.Contains(Class))
        {
            UE_LOG(LogTemp, Warning, TEXT("Service already registered {%s}"), *ServiceClass->GetName());
        }
        else
        {
            T* Instance = NewObject<T>(this, ServiceClass);
            Services.Add(Class, TWeakObjectPtr<>(Instance));
            UE_LOG(LogTemp, Warning, TEXT("Service registered {%s}"), *ServiceClass->GetName());
        }
    }

    template <typename T = UClass>
    void UnregisterService(OnServiceUnregistered OnServiceUnregistered = {})
    {
        auto ServiceClass = T::StaticClass();
        
        if(ServiceClass == nullptr)
            return;
        
        auto Class = T::StaticClass();

        if (Services.Contains(Class))
        {
            Services.Remove(Class);
            OnServiceUnregistered.Execute();
        }
    }

public:
    void Deinitialize();
};
