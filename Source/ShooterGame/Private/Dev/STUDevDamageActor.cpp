// Shoot Then Up Game, All Rights Reserved

#include "STUDevDamageActor.h"
#include "DrawDebugHelpers.h"

ASTUDevDamageActor::ASTUDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
}

