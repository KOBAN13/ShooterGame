// Shoot Then Up Game, All Rights Reserved

#include "Services/TweenService.h"

UTweenService::UTweenService()
{
    ActiveTweens = TArray<FTweenData>();
}

int32 UTweenService::TweenFloat(
    float Start, float End, float Duration, const TFunction<void(float)>& OnUpdate, const TFunction<void()>& OnComplete)
{
    ActiveTweens.Add(FTweenData
        {
            Start,
            End, 
            Duration,
            0.0f,
            NextTweenId++,
            OnUpdate,
            OnComplete
        });

    return NextTweenId;
}

void UTweenService::TweenKill(int32 IdTween)
{
    for (int32 i = 0; i < ActiveTweens.Num(); i++)
    {
        if(ActiveTweens[i].Id == IdTween)
        {
            ActiveTweens.RemoveAt(i);
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

        if(Tween.Elapsed >= Tween.Duration && Tween.OnComplete)
        {
            Tween.OnComplete();
            ActiveTweens.RemoveAt(i);
        }
    }
}


