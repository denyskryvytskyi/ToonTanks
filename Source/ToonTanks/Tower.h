// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void TryFire();

    bool IsInFireRange() const;

private:
    UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRange { 1000.0f };
    
    UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRate { 2.0f };

    class ATank* Tank;

    FTimerHandle FireRateTimerHandle;
};
