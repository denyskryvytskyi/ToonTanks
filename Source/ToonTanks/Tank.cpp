// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    bIsAlive = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    bIsAlive = true;
    TankPlayerController = GetController<APlayerController>();

    if (TankPlayerController) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer())) {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController) {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
                                                      false, HitResult);

        if (HitResult.bBlockingHit) {
            RotateTurret(HitResult.ImpactPoint);
        }
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

        // Shooting
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::FireFromInput);

        // Cursor
        EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Triggered, this, &ATank::Cursor);
    }
}

void ATank::Move(const FInputActionValue& Value)
{
    if (Controller) {
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
        const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

        const FVector2D RotationValue = Value.Get<FVector2D>();

        FRotator DeltaRotation = FRotator::ZeroRotator;
        DeltaRotation.Yaw = RotationValue.X * TurnRate * DeltaTime;

        AddActorLocalRotation(DeltaRotation, true);
    }
}

void ATank::FireFromInput(const FInputActionValue& Value)
{
    Fire();
}

void ATank::Cursor(const FInputActionValue& Value)
{
    if (TankPlayerController) {
        const FVector2D CursorValue = Value.Get<FVector2D>();
        const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

        float MouseX, MouseY;
        TankPlayerController->GetMousePosition(MouseX, MouseY);
        TankPlayerController->SetMouseLocation(CursorValue.X * GamepadCursorSpeed + MouseX, CursorValue.Y * GamepadCursorSpeed + MouseY);
    }
}
