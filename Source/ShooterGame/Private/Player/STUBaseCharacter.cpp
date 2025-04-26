// Shoot Then Up Game, All Rights Reserved

#include "STUBaseCharacter.h"
#include "Engine/DamageEvents.h"
#include "EventBusMacros.h"
#include "EventNameConstants.h"
#include "STUCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EventBusService.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;

    CharacterMovementComponent = Cast<USTUCharacterMovementComponent>(GetCharacterMovement());
    
    CreateComponentsAndAttach();
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
    check(CharacterMovementComponent)
    
    SUBSCRIBE_EVENT(EventNameConstants::OnCharacterDead, 1, [this]() { OnDeath(); });
    
    SUBSCRIBE_STRUCT_EVENT(
        EventNameConstants::OnHealthChanged,
        1,
        FHealthParameters,
        [this](const FHealthParameters* Health) { OnHealthChanged(*Health); }
    );

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundedLanded);
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
    
    SEND_EVENT(EventNameConstants::OnStartRun);
}

void ASTUBaseCharacter::RunEnd()
{
    bIsRun = false;

    SEND_EVENT(EventNameConstants::OnStopRun);
}

void ASTUBaseCharacter::OnDeath()
{
    PlayAnimMontage(DeathAnimation);

    CharacterMovementComponent->DisableMovement();

    SetLifeSpan(5.0f);

    if(Controller)
    {
        Controller -> ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChanged(const FHealthParameters HealthParameters) const
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), HealthParameters.Health)));
}

void ASTUBaseCharacter::OnGroundedLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = GetVelocity().Z;

    UE_LOG(LogBaseCharacter, Warning, TEXT("FallVelocityZ: %f"), FallVelocityZ);

    if(-FallVelocityZ < LandedDamageVelocity.X)
        return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, -FallVelocityZ);

    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
