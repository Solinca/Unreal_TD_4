#include "Player/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!MappingContext)
	{
		return;
	}

	if (ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player))
	{
		if (TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(MappingContext, 0);
		}
	}

	MyChara = Cast<AMyCharacter>(GetPawn());

	DefaultMaxSpeed = MyChara->GetCharacterMovement()->MaxWalkSpeed;

	MyPlayerState = GetPlayerState<AMyPlayerState>();
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (FInputData data : InputDatas)
		{
			EnhancedInputComponent->BindAction(data.Action, data.TriggerType, this, data.ActionName.GetMemberName());
		}
	}
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();

	FRotator CameraRotation = FRotator(0, GetControlRotation().Yaw, 0);

	MyChara->AddMovementInput(CameraRotation.RotateVector(MovementVector));
}

void AMyPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D Values = Value.Get<FVector2D>();

	AddYawInput(Values.X * CameraSensitivity * GetWorld()->GetDeltaSeconds());
	AddPitchInput(Values.Y * CameraSensitivity * GetWorld()->GetDeltaSeconds());
}

void AMyPlayerController::SprintStart(const FInputActionValue& Value)
{
	MyChara->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed * PlayerSprintFactor;
}

void AMyPlayerController::SprintStop(const FInputActionValue& Value)
{
	MyChara->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;
}

void AMyPlayerController::CrouchStart(const FInputActionValue& Value)
{
	MyChara->Crouch();
}

void AMyPlayerController::CrouchStop(const FInputActionValue& Value)
{
	MyChara->UnCrouch();
}

void AMyPlayerController::Grab(const FInputActionValue& Value)
{
	if (MyPlayerState->GrabNearestItem())
	{
		MyPlayerState->GetCurrentlyHeldItem()->AttachToPlayerHand(MyChara->GetMesh(), MyChara->GetItemSocketName());
	}
}

void AMyPlayerController::AimStart(const FInputActionValue& Value)
{
	IsAiming = MyPlayerState->GetCurrentlyHeldItem() != nullptr;
}

void AMyPlayerController::AimStop(const FInputActionValue& Value)
{
	IsAiming = false;
}

void AMyPlayerController::Throw(const FInputActionValue& Value)
{
	if (IsAiming)
	{
		MyPlayerState->GetCurrentlyHeldItem()->ThrowItem(GetControlRotation().Vector() * ThrowForce);

		MyPlayerState->RemoveCurrentlyHeldItem();
	}
}
