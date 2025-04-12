// Shoot Then Up Game, All Rights Reserved

#include "STUCharacterMovementComponent.h"

#include "CharacterConfig.h"
#include "Constants.h"
#include "ResourceLoaderService.h"
#include "STUGameInstance.h"
#include "ServiceLocatorSubsystem.h"
#include "TweenService.h"
#include "EventBus/EventBusService.h"

void USTUCharacterMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();
    Initialize();
}

void USTUCharacterMovementComponent::RunStart(USTUCharacterMovementComponent* Component)
{
    UTweenService* TweenService = nullptr;
    
    if(ServiceLocator -> TryGetService(TweenService))
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
}

void USTUCharacterMovementComponent::RunEnd(USTUCharacterMovementComponent* Component)
{
    UTweenService* TweenService = nullptr;

    if (ServiceLocator->TryGetService(TweenService))
    {
        TweenService->TweenKill(IdTweenRunEnd);
        IdTweenRunEnd = TweenService->TweenFloat(
            CharacterConfig->MaxSpeed, CharacterConfig->MaxSpeed, CharacterConfig->TimeInterpolation, [this](float Speed)
            { MaxWalkSpeed = Speed; }, []() { GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("RunEnd")); });
    }
}

void USTUCharacterMovementComponent::OnCharacterConfigLoaded()
{
    UResourceLoaderService* ResourceLoaderService = nullptr;
    
    if(ServiceLocator -> TryGetService(ResourceLoaderService))
    {
        UDataAsset* DataAsset = ResourceLoaderService
            -> GetResource(Constants::CharacterConfig);

        check(DataAsset->IsValidLowLevel())

        CharacterConfig = Cast<UCharacterConfig>(DataAsset);
        MaxWalkSpeed = CharacterConfig -> MaxSpeed;
    }
}

void USTUCharacterMovementComponent::Initialize()
{
    if (const auto* World = GetWorld())
    {
        if (const auto* GameInstance = Cast<USTUGameInstance>(World -> GetGameInstance()))
        {
            ServiceLocator = GameInstance->GetServiceLocator();

            UResourceLoaderService* ResourceLoaderService = nullptr;

            if (ServiceLocator->TryGetService(ResourceLoaderService))
            {
                ResourceLoaderService->OnCharacterConfigLoaded.AddUObject(this, &USTUCharacterMovementComponent::OnCharacterConfigLoaded);
            }

            UEventBusService* EventBus = nullptr;
            ServiceLocator -> TryGetService(EventBus);

            check(EventBus != nullptr);

            EventBus -> Subscribe<USTUCharacterMovementComponent>(1, [this](USTUCharacterMovementComponent* Component)
            {
                Component -> RunStart(Component);
            });

            EventBus -> Subscribe<USTUCharacterMovementComponent>(2, [this](USTUCharacterMovementComponent* Component)
            {
                Component -> RunEnd(Component);
            });
        }
    } 
}
   