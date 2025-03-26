// Shoot Then Up Game, All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "UServiceManager.generated.h"

DECLARE_DELEGATE(OnServiceUnregistered);

UCLASS()
class SHOOTERGAME_API UServiceManager : public UObject
{
    GENERATED_BODY()

private:
    TMap<UClass*, TWeakObjectPtr<>> Services;

private:
    void InitializeFields();

public:
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
    void UnregisterService(T* ServiceClass, OnServiceUnregistered OnServiceUnregistered)
    {
        UClass* Class = T::StaticClass();

        if (Services.Contains(Class) && Services[ServiceClass] == Class)
        {
            Services.Remove(Class);
            OnServiceUnregistered.Execute();
        }
    }
};
