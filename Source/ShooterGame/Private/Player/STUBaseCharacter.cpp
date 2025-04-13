// Shoot Then Up Game, All Rights Reserved

#include "STUBaseCharacter.h"

#include "EventNameConstants.h"
#include "STUCharacterMovementComponent.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EventBusService.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLogs, All, All);

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    CharacterMovementComponent = Cast<USTUCharacterMovementComponent>(GetCharacterMovement());
    
    CreateComponentsAndAttach();

    if (const auto* World = GetWorld())
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World -> GetGameInstance()))
        {
            const auto* ServiceLocator = GameInstance->GetServiceLocator();

            EventBus = nullptr;

            if(ServiceLocator -> TryGetService(EventBus))
            {
                check(EventBus != nullptr);
            }
        }
    } 
}

bool ASTUBaseCharacter::IsRunning() const
{
    return bIsRun && bIsWalk && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetWalkDirection() const
{
    const auto Velocity = GetVelocity();

    if(Velocity.IsZero())
        return 0.0f;
    
    const auto ForwardVector = GetActorForwardVector();

    const auto NormalizeVelocity = UKismetMathLibrary :: Normal(Velocity);
    const auto DotProduct = UKismetMathLibrary::Dot_VectorVector(NormalizeVelocity, ForwardVector);
    const auto CrossProduct = UKismetMathLibrary::Cross_VectorVector(NormalizeVelocity, ForwardVector);
    const auto AngleBetween = UKismetMathLibrary::DegAcos(DotProduct);
    const auto SignAngle = UKismetMathLibrary::SignOfFloat(CrossProduct.Z);

    return CrossProduct.IsZero() ? AngleBetween : AngleBetween * SignAngle;
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    BindInputAxis(PlayerInputComponent);
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthTextComponent)
    check(HealthComponent)
}

void ASTUBaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto Health = HealthComponent->GetHealth();
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    FVector ForwardDirection = GetActorForwardVector();
    AddMovementInput(ForwardDirection, Amount);

    bIsWalk = Amount > 0.0f;
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
    SpringArmComponent -> SetupAttachment(GetRootComponent());
    SpringArmComponent -> bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent -> SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRenderer");
    HealthTextComponent -> SetupAttachment(GetRootComponent());
}

void ASTUBaseCharacter::RunStart()
{
    bIsRun = true;

    EventBus -> SendEvent(EventNameConstants::OnStartRun);
}

void ASTUBaseCharacter::RunEnd()
{
    bIsRun = false;

    EventBus->SendEvent(EventNameConstants::OnStopRun);
}
