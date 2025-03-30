// Shoot Then Up Game, All Rights Reserved

#include "Services/TweenService.h"

UTweenService::UTweenService()
{
    ActiveTweens = TArray<FTweenData>();
}

void UTweenService::TweenFloat(
    float Start,
    float End,
    float Duration,
    const TFunction<void(float)>& OnUpdate,
    const TFunction<void()>& OnComplete
)
{
    ActiveTweens.Add(FTweenData{Start, End, Duration, 0.0f, OnUpdate, OnComplete});
}

void UTweenService::Tick(float DeltaTime)
{
    for (int32 i = ActiveTweens.Num() - 1; i >= 0; i--)
    {
        auto Tween = ActiveTweens[i];
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


