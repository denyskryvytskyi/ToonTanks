// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "BasePawn.h"
#include "Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
    RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(CapsuleComp);
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
    if (DeathParticles)
    {
        UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation());
    }

    if (DeathSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
    }

    if (DeathCameraShakeClass)
    {
        GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
    }
}

void ABasePawn::RotateTurret(const FVector& LookAtTarget)
{
    const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();

    const FRotator LookAtRotation(0.0f, ToTarget.Rotation().Yaw, 0.0f);

    TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),
                                 LookAtRotation,
                                 UGameplayStatics::GetWorldDeltaSeconds(this),
                                 RotationInterpSpeed));
}

void ABasePawn::Fire()
{
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
                                                          ProjectileSpawnPoint->GetComponentLocation(),
                                                          ProjectileSpawnPoint->GetComponentRotation());

    Projectile->SetOwner(this);
}
