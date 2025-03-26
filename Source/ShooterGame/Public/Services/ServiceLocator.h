// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ServiceLocator.generated.h"

UCLASS()
class SHOOTERGAME_API AServiceLocator : public AActor
{
	GENERATED_BODY()
	
public:	
	AServiceLocator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
