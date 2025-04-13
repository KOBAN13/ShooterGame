// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTERGAME_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;
    
	ASTUDevDamageActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
