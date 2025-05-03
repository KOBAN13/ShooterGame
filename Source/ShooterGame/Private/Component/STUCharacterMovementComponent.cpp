// Shoot Then Up Game, All Rights Reserved

#include "STUCharacterMovementComponent.h"

#include "CharacterConfig.h"
#include "ConstantsLoader.h"
#include "EventBusMacros.h"
#include "EventNameConstants.h"
#include "ResourceLoaderService.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "TweenService.h"

void USTUCharacterMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();
    Initialize();
}

void USTUCharacterMovementComponent::RunStart()
{
    TweenService -> TweenKill(IdTweenRunStart);
    IdTweenRunStart = TweenService -> TweenFloat(CharacterConfig -> MaxSpeed,
        CharacterConfig -> RunSpeed,
        CharacterConfig -> TimeInterpolation,
        [this](float Speed)
        {
            MaxWalkSpeed = Speed;
        },
        []() { GEngine -> AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("RunStart")); }
        );
}

void USTUCharacterMovementComponent::RunEnd()
{
    TweenService->TweenKill(IdTweenRunEnd);
    IdTweenRunEnd = TweenService->TweenFloat(
        CharacterConfig->MaxSpeed, CharacterConfig->MaxSpeed, CharacterConfig->TimeInterpolation, [this](float Speed)
        { MaxWalkSpeed = Speed; }, []() { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("RunEnd")); });
}

void USTUCharacterMovementComponent::OnCharacterConfigLoaded()
{
    UDataAsset* DataAsset = ResourceLoaderService
    -> GetResource(ConstantsLoader::CharacterConfig);

    check(DataAsset)

    CharacterConfig = Cast<UCharacterConfig>(DataAsset);
    MaxWalkSpeed = CharacterConfig -> MaxSpeed;
}

void USTUCharacterMovementComponent::Initialize()
{
    if (const auto* World = GetWorld())
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World -> GetGameInstance()))
        {
            const auto* ServiceLocator = GameInstance->GetServiceLocator();

            if (ServiceLocator->TryGetService(ResourceLoaderService))
            {
                ResourceLoaderService->OnCharacterConfigLoaded.AddUObject(this, &USTUCharacterMovementComponent::OnCharacterConfigLoaded);
            }

            ServiceLocator -> TryGetService(TweenService);

            check(TweenService)
            check(ResourceLoaderService)

            Subscribe<void, UObjectEventBusService>(EventNameConstants::OnStartRun, 1, [this](void*) { RunStart(); }, World);
            Subscribe<void, UObjectEventBusService>(EventNameConstants::OnStopRun, 1, [this](void*) { RunEnd(); }, World);
        }
    } 
}
   