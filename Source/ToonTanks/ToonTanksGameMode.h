// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
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
    int32 TargetTowersAmount { 4 };
};
