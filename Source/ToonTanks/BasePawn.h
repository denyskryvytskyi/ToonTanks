// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn {
    GENERATED_BODY()

public:
    ABasePawn();

    virtual void HandleDestruction();

protected:
    void RotateTurret(const FVector& LookAtTarget);
    void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UCapsuleComponent* CapsuleComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* TurretMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USceneComponent* ProjectileSpawnPoint;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    TSubclassOf<class AProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    class UParticleSystem* DeathParticles;

    UPROPERTY(EditAnywhere, Category = "Combat")
    class USoundBase* DeathSound;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float RotationInterpSpeed { 5.0f };
};
