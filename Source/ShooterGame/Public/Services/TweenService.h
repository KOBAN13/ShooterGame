// Shoot Then Up Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "TweenService.generated.h"

UCLASS()
class SHOOTERGAME_API UTweenService : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
    UTweenService();

    int32 TweenFloat(
        float Start,
        float End,
        float Duration,
        const TFunction<void(float)>& OnUpdate,
        const TFunction<void()>& OnComplete = nullptr
    );

    int32 SteppedTweenFloat(
        float StartValue,
        float EndValue,
        float StepSize,
        float StepInterval,
        float InitialDelay = 0.0f,
        const TFunction<void(float)>& OnUpdate = nullptr,
        const TFunction<void()>& OnComplete = nullptr
    );

    void TweenKill(int32 IdTween);
    void SteppedTweenKill(int32 IdTween);

    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override { return true; }
    virtual bool IsTickableInEditor() const override { return false; }
    virtual bool IsTickableWhenPaused() const override { return false; }
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UYourObject, STATGROUP_Tickables); }

private:
    struct FTweenData
    {
        float Start;
        float End;
        float Duration;
        float Elapsed;
        int32 Id;
        TFunction<void(float)> OnUpdate;
        TFunction<void()> OnComplete;
    };

    struct FSteppedTweenData
    {
        float StartValue;
        float EndValue;
        float StepSize;
        float StepInterval;
        float InitialDelay;
        int32 Id;       
        const TFunction<void(float)>& OnUpdate;
        const TFunction<void()>& OnComplete;
    }; 
    
    int32 NextTweenId = 0;

    TArray<FTweenData> ActiveTweens;
    TArray<FSteppedTweenData> ActiveSteppedTweens;

    FTimerHandle DelayTimer;
    FTimerHandle StepTimer;

    void SteppedTweenStart(FSteppedTweenData& SteppedTween);
    void ApplySteppedTween(FSteppedTweenData& SteppedTween);
    static bool IsSteppedTweenComplete(const FSteppedTweenData& SteppedTween);
};
