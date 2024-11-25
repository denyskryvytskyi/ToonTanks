// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "BasePawn.h"
#include "CoreMinimal.h"
#include "InputActionValue.h"

#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn {
    GENERATED_BODY()

public:
    ATank();

    virtual void HandleDestruction() override;

    APlayerController* GetPlayerController() const { return TankPlayerController; }

    bool IsAlive() const { return bIsAlive; }

protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    void Move(const FInputActionValue& Value);
    void Turn(const FInputActionValue& Value);
    void FireFromInput(const FInputActionValue& Value);
    void Cursor(const FInputActionValue& Value);

private:
    /** Components **/
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* CameraComp;

    /** Input */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* TurnAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* FireAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* CursorAction;

    /** Parameters*/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float Speed { 200.0f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    float TurnRate { 100.0f };

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
    float GamepadCursorSpeed { 10.0f };

    APlayerController* TankPlayerController;

    bool bIsAlive { false };
};
