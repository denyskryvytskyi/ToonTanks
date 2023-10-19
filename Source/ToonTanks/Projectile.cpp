// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
    RootComponent = ProjectileMesh;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

    TrailParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle System"));
    TrailParticleSystemComp->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if (LaunchSound)
	{
         UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
    }
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto MyOwner = GetOwner())
	{
        auto OwnerInstigator = Owner->GetInstigatorController();
        auto DamageTypeClass = UDamageType::StaticClass();

		if (OtherActor && OtherActor != this && OtherActor != MyOwner)
		{
            if (HitSound)
			{
                UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
            }

            UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
            if (HitParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
		}
	}

    Destroy();
}

