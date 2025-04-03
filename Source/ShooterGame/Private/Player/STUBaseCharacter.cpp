// Shoot Then Up Game, All Rights Reserved

#include "STUBaseCharacter.h"

#include "ResourceLoaderService.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "TweenService.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Config/CharacterConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Helpers/Constants.h"

ASTUBaseCharacter::ASTUBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    CreateComponentsAndAttach();
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    USTUGameInstance* GameInstance = Cast<USTUGameInstance>(GetGameInstance());
    ServiceLocator = GameInstance -> GetServiceLocatorSubsystem();
    
    UResourceLoaderService* ResourceLoaderService = nullptr;
    
    if(ServiceLocator -> TryGetService(ResourceLoaderService))
    {
        CharacterConfig = Cast<UCharacterConfig>(ResourceLoaderService
            -> GetResource(Constants::CharacterConfig));
    }
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    BindInputAxis(PlayerInputComponent);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    FVector ForwardDirection = GetActorForwardVector();
    AddMovementInput(ForwardDirection, Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    FVector RigthDirection = GetActorRightVector();
    AddMovementInput(RigthDirection, Amount);
}

void ASTUBaseCharacter::LookUp(float Amount)
{
    AddControllerPitchInput(Amount);
}

void ASTUBaseCharacter::TurnAround(float Amount)
{
    AddControllerYawInput(Amount); 
}

void ASTUBaseCharacter::BindInputAxis(UInputComponent* PlayerInputComponent)
{
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::TurnAround);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::LookUp);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("RunStart", IE_Pressed, this, &ASTUBaseCharacter::RunStart);
    PlayerInputComponent->BindAction("RunEnd", IE_Released, this, &ASTUBaseCharacter::RunEnd);
}

void ASTUBaseCharacter::CreateComponentsAndAttach()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("ArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    GetCharacterMovement() -> MaxWalkSpeed = CharacterConfig -> MaxSpeed;
}

void ASTUBaseCharacter::RunStart()
{
    auto CurrentMaxSpeed = GetCharacterMovement() -> MaxWalkSpeed;

    UTweenService* TweenService = nullptr;
    
    if(ServiceLocator -> TryGetService(TweenService))
    {
        TweenService -> TweenKill(IdTweenRunStart);
        IdTweenRunStart = TweenService -> TweenFloat(CurrentMaxSpeed,
            CharacterConfig -> RunSpeed,
            CharacterConfig -> TimeInterpolation,
            [this](float Speed)
            {
                GetCharacterMovement() -> MaxWalkSpeed = Speed;
            },
            []() { GEngine -> AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("RunStart")); }
            );
    }
}

void ASTUBaseCharacter::RunEnd()
{
    float CurrentMaxSpeed = GetCharacterMovement() -> MaxWalkSpeed;

    UTweenService* TweenService = nullptr;

    if(ServiceLocator -> TryGetService(TweenService))
    {
        TweenService -> TweenKill(IdTweenRunEnd);
        IdTweenRunEnd = TweenService -> TweenFloat(CurrentMaxSpeed,
            CharacterConfig -> MaxSpeed,
            CharacterConfig -> TimeInterpolation,
            [this](float Speed)
            {
                GetCharacterMovement() -> MaxWalkSpeed = Speed;
            },
            []() { GEngine -> AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("RunEnd")); }
            );
    }
}
