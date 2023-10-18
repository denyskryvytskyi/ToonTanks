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

public:
    virtual void HandleDestruction() override;

protected:
    virtual void BeginPlay() override;

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
