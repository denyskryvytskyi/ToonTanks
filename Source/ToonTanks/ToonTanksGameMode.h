// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase {
    GENERATED_BODY()

public:
    void ActorDied(AActor* Actor);

protected:
    virtual void BeginPlay() override;

    void HandleGameStart();

    int32 GetTargetTowerCount() const;

    /** Blueprint Implementable Events*/
    UFUNCTION(BlueprintImplementableEvent)
    void StartGame();

    UFUNCTION(BlueprintImplementableEvent)
    void GameOver(bool bIsWon);

private:
    class ATank* Tank;
    class AToonTanksPlayerController* ToonTanksPlayerController;

    float StartDelay { 3.0f };
    float RestartLevelDelay { 3.0f };

    UPROPERTY(EditAnywhere, category = "Game Logic")
    int32 TargetTowersAmount { 4 };
};
