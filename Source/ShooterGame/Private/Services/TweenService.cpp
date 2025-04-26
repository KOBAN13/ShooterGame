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
    const auto SafeOnComplete = OnComplete ? OnComplete : []() {};
    const auto SafeOnUpdate = OnUpdate ? OnUpdate : [](float Value) {};
    
    ActiveTweens.Add(FTweenData{Start, End, Duration, 0.0f, NextTweenId++, SafeOnUpdate, SafeOnComplete});

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
    const auto SafeOnUpdate = OnUpdate ? OnUpdate : [](float Value) {};
    const auto SafeOnComplete = OnComplete ? OnComplete : []() {};

    FTimerHandle DelayTimer;
    FTimerHandle StepTimer;

    NextTweenId++;
    
    ActiveSteppedTweens.Add(FSteppedTweenData{StartValue, EndValue, StepSize, StepInterval, InitialDelay, NextTweenId, DelayTimer, StepTimer, SafeOnUpdate, SafeOnComplete});
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
            auto& SteppedTween = ActiveSteppedTweens[i];
            GetWorld()->GetTimerManager().ClearTimer(SteppedTween.DelayTimer);
            GetWorld()->GetTimerManager().ClearTimer(SteppedTween.StepTimer);
            
            ActiveSteppedTweens.RemoveAt(i);
            
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
        GetWorld() -> GetTimerManager()
        .SetTimer(
            SteppedTween.DelayTimer,
            [this, TweenId = SteppedTween.Id]()
            {
                if(auto* SteppedTweenData = FindSteppedTweenIndex(TweenId))
                    ApplySteppedTween(*SteppedTweenData);
            },
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
    SteppedTween.OnUpdate(SteppedTween.StartValue);
    
    if (IsSteppedTweenComplete(SteppedTween))
    {
        SteppedTween.StartValue = SteppedTween.EndValue;
        SteppedTween.OnUpdate(SteppedTween.StartValue);
        SteppedTween.OnComplete();
        SteppedTweenKill(SteppedTween.Id);
        return;
    }
    
    const bool bIsIncreasing = SteppedTween.EndValue > SteppedTween.StartValue;

    SteppedTween.StartValue += bIsIncreasing ? SteppedTween.StepSize : -SteppedTween.StepSize;

    if ((bIsIncreasing && SteppedTween.StartValue > SteppedTween.EndValue) ||
        (!bIsIncreasing && SteppedTween.StartValue < SteppedTween.EndValue))
    {
        SteppedTween.StartValue = SteppedTween.EndValue;
    }

    GetWorld() -> GetTimerManager()
    .SetTimer(
        SteppedTween.StepTimer,
        [this, TweenId = SteppedTween.Id]()
        {
            if(auto* SteppedTweenData = FindSteppedTweenIndex(TweenId))
                ApplySteppedTween(*SteppedTweenData);
        },
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

UTweenService::FSteppedTweenData* UTweenService::FindSteppedTweenIndex(int32 IdTween)
{
    return ActiveSteppedTweens.FindByPredicate([IdTween](const FSteppedTweenData& SteppedTween)
    {
        return SteppedTween.Id == IdTween;
    });
}




