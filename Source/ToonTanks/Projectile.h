// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor {
    GENERATED_BODY()

public:
    AProjectile();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Combat")
    UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    class UProjectileMovementComponent* MovementComp;

    UPROPERTY(VisibleAnywhere, Category = "Combat")
    class UParticleSystemComponent* TrailParticleSystemComp;

    UPROPERTY(EditAnywhere)
    float Damage { 50.0f };

    UPROPERTY(EditAnywhere, Category = "Combat")
    class UParticleSystem* HitParticles;

    UPROPERTY(EditAnywhere, Category = "Combat")
    class USoundBase* LaunchSound;

    UPROPERTY(EditAnywhere, Category = "Combat")
    USoundBase* HitSound;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
