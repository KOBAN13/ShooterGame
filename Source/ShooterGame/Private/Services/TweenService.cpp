// Shoot Then Up Game, All Rights Reserved

#include "TweenService.h"

UTweenService::UTweenService()
{
    ActiveTweens = TArray<FTweenData>();
    ActiveSteppedTweens = TArray<FSteppedTweenData>();
}

int32 UTweenService::TweenFloat(
    const float Start,
    const float End,
    const float Duration,
    const TFunction<void(float)>& OnUpdate,
    const TFunction<void()>& OnComplete
)
{
    auto SafeOnComplete = OnComplete ? OnComplete : []() {};
    
    ActiveTweens.Add(FTweenData{Start, End, Duration, 0.0f, NextTweenId++, OnUpdate, OnComplete});

    return NextTweenId;
}

int32 UTweenService::SteppedTweenFloat(
    const float StartValue,
    const float EndValue,
    const float StepSize,
    const float StepInterval,
    const float InitialDelay,
    const TFunction<void(float)>& OnUpdate,
    const TFunction<void()>& OnComplete
)
{
    auto SafeOnUpdate = OnUpdate ? OnUpdate : [](float Value) {};
    auto SafeOnComplete = OnComplete ? OnComplete : []() {};
    
    ActiveSteppedTweens.Add(FSteppedTweenData{StartValue, EndValue, StepSize, StepInterval, InitialDelay, NextTweenId++, OnUpdate, OnComplete});
    SteppedTweenStart(ActiveSteppedTweens.Last());
    return NextTweenId; 
}

void UTweenService::TweenKill(int32 IdTween)
{
    for (int32 i = 0; i < ActiveTweens.Num(); i++)
    {
        if (ActiveTweens[i].Id == IdTween)
        {
            ActiveTweens.RemoveAt(i);
            break;
        }
    }
}

void UTweenService::SteppedTweenKill(int32 IdTween)
{
    for (int32 i = 0; i < ActiveSteppedTweens.Num(); i++)
    {
        if(ActiveSteppedTweens[i].Id == IdTween)
        {
            ActiveSteppedTweens.RemoveAt(i);

            GetWorld()->GetTimerManager().ClearTimer(DelayTimer);
            GetWorld()->GetTimerManager().ClearTimer(StepTimer);
            
            break;
        }
    }
}

void UTweenService::Tick(float DeltaTime)
{
    for (int32 i = 0; i < ActiveTweens.Num(); i++)
    {
        auto& Tween = ActiveTweens[i];
        Tween.Elapsed += DeltaTime;
        auto Alpha = FMath::Clamp(Tween.Elapsed / Tween.Duration, 0.0f, 1.0f);
        auto Value = FMath::Lerp(Tween.Start, Tween.End, Alpha);
        Tween.OnUpdate(Value);

        if (Tween.Elapsed >= Tween.Duration && Tween.OnComplete)
        {
            Tween.OnComplete();
            ActiveTweens.RemoveAt(i);
        }
    }
}

void UTweenService::SteppedTweenStart(FSteppedTweenData& SteppedTween)
{
    if (FMath::IsNearlyEqual(SteppedTween.StartValue, SteppedTween.EndValue, 0.01f))
        return;

    if (SteppedTween.InitialDelay > 0.0f)
    {
        UWorld* World = GetWorld();
        FTimerManager &TimerManager = World -> GetTimerManager();
        
        TimerManager
        .SetTimer(
            DelayTimer,
            [this, &SteppedTween]() { ApplySteppedTween(SteppedTween); },
            SteppedTween.InitialDelay,
            false
        );
    }
    else
    {
        ApplySteppedTween(SteppedTween);
    }

    if(IsSteppedTweenComplete(SteppedTween))
    {
        SteppedTween.OnComplete();
    }
}

void UTweenService::ApplySteppedTween(FSteppedTweenData& SteppedTween)
{
    const bool bIsIncreasing = SteppedTween.EndValue > SteppedTween.StartValue;

    SteppedTween.StartValue += bIsIncreasing ? SteppedTween.StepSize : -SteppedTween.StepSize;

    if (IsSteppedTweenComplete(SteppedTween))
    {
        SteppedTween.StartValue = SteppedTween.EndValue;
        SteppedTween.OnUpdate(SteppedTween.StartValue);
        SteppedTween.OnComplete();
        SteppedTweenKill(SteppedTween.Id);
        return;
    }

    if ((bIsIncreasing && SteppedTween.StartValue >= SteppedTween.EndValue) ||
        (!bIsIncreasing && SteppedTween.StartValue <= SteppedTween.EndValue))
    {
        SteppedTween.StartValue = SteppedTween.EndValue;
        SteppedTween.OnUpdate(SteppedTween.StartValue);
        SteppedTweenKill(SteppedTween.Id);
        return;
    }

    SteppedTween.OnUpdate(SteppedTween.StartValue);

    UWorld* World = GetWorld();
    FTimerManager &TimerManager = World -> GetTimerManager();
    
    TimerManager.SetTimer(
        StepTimer,
        [this, &SteppedTween]() { ApplySteppedTween(SteppedTween); },
        SteppedTween.StepInterval,
        false
    );
}

bool UTweenService::IsSteppedTweenComplete(const FSteppedTweenData& SteppedTween)
{
    return FMath::IsNearlyEqual(SteppedTween.StartValue, SteppedTween.EndValue, 0.01f) ||
        (SteppedTween.StepSize > 0.0f && SteppedTween.StartValue >= SteppedTween.EndValue) ||
            (SteppedTween.StepSize < 0.0f && SteppedTween.StartValue < SteppedTween.EndValue);
}


