// Copyright Denys Kryvytskyi. All Rights Reserved.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor* Actor)
{
    if (Actor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        GameOver(false);

        FTimerHandle LevelRestartTimerHandle;
        FTimerDelegate LevelRestartTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
            &AToonTanksPlayerController::RestartLevel);

        GetWorldTimerManager().SetTimer(LevelRestartTimerHandle, LevelRestartTimerDelegate, RestartLevelDelay, false);
    }
    else if (ATower* Destroyed = Cast<ATower>(Actor))
    {
        Destroyed->HandleDestruction();
        --TargetTowersAmount;
        if (TargetTowersAmount == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowersAmount = GetTargetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);

        FTimerHandle PlayerEnableTimerHandle;

        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState, true);

        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
    }
}

int32 AToonTanksGameMode::GetTargetTowerCount() const
{
    TArray<AActor*> TowersArray;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), TowersArray);

    return TowersArray.Num();
}
