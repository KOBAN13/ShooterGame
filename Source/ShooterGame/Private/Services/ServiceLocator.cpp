// Shoot Then Up Game, All Rights Reserved

#include "Services/ServiceLocator.h"

AServiceLocator::AServiceLocator()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AServiceLocator::BeginPlay()
{
	Super::BeginPlay();
	
}


void AServiceLocator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

