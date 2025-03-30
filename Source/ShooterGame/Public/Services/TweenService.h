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

    void TweenFloat(
        float Start,
        float End,
        float Duration,
        const TFunction<void(float)>& OnUpdate,
        const TFunction<void()>& OnComplete = nullptr
    );

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
        TFunction<void(float)> OnUpdate;
        TFunction<void()> OnComplete;
    };

    TArray<FTweenData> ActiveTweens;
};
