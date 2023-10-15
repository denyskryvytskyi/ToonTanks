// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

ATank::ATank()
    : ABasePawn()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComp->SetupAttachment(RootComponent);
    
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = GetController<APlayerController>();

    if (PlayerControllerRef) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerControllerRef->GetLocalPlayer())) {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
                                                     false, HitResult);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 
                        20.0f, 32, FColor::Red, false);
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);

        // Turning around
        EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::Turn);
    }
}

#pragma optimize("", off)
void ATank::Move(const FInputActionValue& Value)
{
    if (Controller)
    {
        UE_LOG(LogTemp, Display, TEXT("Moving..."));

        const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

        const FVector2D MovementVector = Value.Get<FVector2D>();
        
        FVector DeltaLocation(0.f);
        DeltaLocation.X = MovementVector.Y * Speed * DeltaTime;

        AddActorLocalOffset(DeltaLocation, true);
    }
}

void ATank::Turn(const FInputActionValue& Value)
{
    if (Controller) {
        UE_LOG(LogTemp, Display, TEXT("Turning around..."));

        const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

        const FVector2D RotationValue = Value.Get<FVector2D>();

        FRotator DeltaRotation = FRotator::ZeroRotator;
        DeltaRotation.Yaw = RotationValue.X * TurnRate * DeltaTime;

        AddActorLocalRotation(DeltaRotation, true);
    }
}
