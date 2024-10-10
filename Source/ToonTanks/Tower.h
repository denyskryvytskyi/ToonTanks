// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "BasePawn.h"
#include "CoreMinimal.h"

#include "Tower.generated.h"

UCLASS()
class TOONTANKS_API ATower : public ABasePawn {
    GENERATED_BODY()

public:
    virtual void HandleDestruction() override;

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    void TryFire();

    bool CanFire() const;

private:
    UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRange { 1000.0f };

    UPROPERTY(EditAnywhere, Category = "Combat", meta = (AllowPrivateAccess = "true"))
    float FireRate { 2.0f };

    class ATank* Tank;

    FTimerHandle FireRateTimerHandle;
};
