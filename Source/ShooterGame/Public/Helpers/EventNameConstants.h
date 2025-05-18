#pragma once

#include "CoreMinimal.h"
#include "ConstantsMacros.h"

namespace EventNameConstants
{
    static const FName OnStartRun = NAMEOF(OnStartRun);
    static const FName OnStopRun = NAMEOF(OnStopRun);
    static const FName OnCharacterDead = NAMEOF(OnCharacterDead);
    static const FName OnHealthChanged = NAMEOF(OnHealthChanged);
    static const FName OnCharacterConfigLoaded = NAMEOF(OnCharacterConfigLoaded);
    static const FName OnBaseWeaponConfigLoaded = NAMEOF(OnBaseWeaponConfigLoaded);
}
