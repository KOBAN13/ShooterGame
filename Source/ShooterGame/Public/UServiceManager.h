// Shoot Then Up Game, All Rights Reserved
#pragma once

#include "CoreMinimal.h"
#include "UServiceManager.generated.h"

UCLASS()
class SHOOTERGAME_API UServiceManager : public UObject
{
    GENERATED_BODY()

private:
    TMap<UClass*, TSharedPtr<UObject>> Services;

private:
    void InitializeFields();

public:
    UServiceManager();
    virtual ~UServiceManager() override;

public:
    template <typename T = UObject>
    bool TryGetService(T*& OutService)
    {
        UClass* Class = T::StaticClass();
        TSharedPtr<UObject>* FindService = Services.Find(Class);

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
            Services.Add(Class, TSharedPtr<UObject>(Instance));
            UE_LOG(LogTemp, Warning, TEXT("Service registered {%s}"), *ServiceClass->GetName());
        }
    }
};
