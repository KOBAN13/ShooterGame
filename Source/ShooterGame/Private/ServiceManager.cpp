// Shoot Then Up Game, All Rights Reserved


#include "ServiceManager.h"

ServiceManager::ServiceManager()
{
}

void ServiceManager::InitializeFields()
{
    Services = TMap<UClass*, TSharedPtr<UObject>>();
}

ServiceManager::~ServiceManager()
{
    Services.Empty();
}
