// Shoot Then Up Game, All Rights Reserved

#include "STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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

    const auto* World = GetWorld();
    const auto ActorLocation = GetActorLocation();

    DrawDebugSphere(World, ActorLocation, Radius, 24, SphereColor);

    UGameplayStatics::ApplyRadialDamage(World, Damage, ActorLocation, Radius, DamageTypeClass, {}, this, nullptr, DoFullDamage);
}

