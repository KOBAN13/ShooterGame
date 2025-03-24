// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"

class SHOOTERGAME_API ServiceManager
{

private:
     TMap<UClass*, TSharedPtr<UObject>> Services;
    
public:
	ServiceManager();
    void InitializeFields();
	~ServiceManager();

public:
    template<typename T>
    bool TryGetService(T*& OutService)
    {
        UClass* Class = T::StaticClass();
        TSharedPtr<UObject>* FindService = Services.Find(Class);

        if(FindService && FindService -> IsValid())
        {
            OutService = Cast<T>(FindService -> Get());
            return true;
        }

        OutService = nullptr;
        return false;
    }

    template<typename T>
    void RegisterService(TSubclassOf<T> ServiceClass)
    {
        UClass* Class = ServiceClass.Get();
        
        if(Services.Contains(Class))
        {
            UE_LOG(LogTemp, Warning, TEXT("Service already registered {%s}"), *ServiceClass->GetName());
        }
        else
        {
            T* Instance = NewObject<T>(GetTransientPackage(), ServiceClass);
            Services.Add(Class, TSharedPtr<UObject>(Instance));
            UE_LOG(LogTemp, Warning, TEXT("Service registered {%s}"), *ServiceClass->GetName());
        }
    }
};
