// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bIsPlayerEnabled)
{
    if (bIsPlayerEnabled) {
        GetPawn()->EnableInput(this);
    } else {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bIsPlayerEnabled;
}
