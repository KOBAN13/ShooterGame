// Shoot Then Up Game, All Rights Reserved

#include "ShooterGame/Public/Player/STUBaseCharacter.h"

ASTUBaseCharacter::ASTUBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASTUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

