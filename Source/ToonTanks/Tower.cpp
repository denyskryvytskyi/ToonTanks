// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"

#include "TimerManager.h"

#include "Kismet/GameplayStatics.h"


void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, 
                                    &ATower::TryFire, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Tank)
    {
        if (IsInFireRange())
        {
            RotateTurret(Tank->GetActorLocation());
        }
    }
}

void ATower::TryFire()
{
    if (IsInFireRange())
    {
        Fire();
    }
}

bool ATower::IsInFireRange() const
{
    return Tank && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}
