// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "Tower.h"
#include "Tank.h"

#include "TimerManager.h"

#include "Kismet/GameplayStatics.h"

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

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

    if (CanFire()) {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::TryFire()
{
    if (CanFire()) {
        Fire();
    }
}

bool ATower::CanFire() const
{
    return Tank && Tank->IsAlive() && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}
