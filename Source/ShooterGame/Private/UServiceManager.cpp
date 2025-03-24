// Shoot Then Up Game, All Rights Reserved

#include "UServiceManager.h"

UServiceManager::UServiceManager()
{
    InitializeFields();
}

void UServiceManager::InitializeFields()
{
    Services = TMap<UClass*, TSharedPtr<UObject>>();
}

UServiceManager::~UServiceManager()
{
    Services.Empty();
}
