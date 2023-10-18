// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool bIsPlayerEnabled)
{
    if (bIsPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    } else {
        GetPawn()->DisableInput(this);
    }

    bShowMouseCursor = bIsPlayerEnabled;
}
