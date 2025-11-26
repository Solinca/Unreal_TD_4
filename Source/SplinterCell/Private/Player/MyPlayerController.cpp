#include "Player/MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
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

	MyGameState = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	MyGameState->OnPlayerDeath.AddUniqueDynamic(this, &AMyPlayerController::OnPlayerDeath);

	MyGameState->OnPlayerVictory.AddUniqueDynamic(this, &AMyPlayerController::OnPlayerVictory);

	MyPlayerState = GetPlayerState<AMyPlayerState>();

	MyPlayerState->RegisterNewCheckpoint(MyChara->GetActorLocation(), GetControlRotation());

	MyPlayerState->OnPlayerEnterHideSpot.AddUniqueDynamic(this, &AMyPlayerController::OnPlayerEnterHideSpot);

	MyPlayerState->OnPlayerExitHideSpot.AddUniqueDynamic(this, &AMyPlayerController::OnPlayerExitHideSpot);

	PauseMenu->OnResumeGame.AddUniqueDynamic(this, &AMyPlayerController::OnResumeGame);

	PauseMenu->OnQuitGame.AddUniqueDynamic(this, &AMyPlayerController::OnQuitGame);
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

void AMyPlayerController::OpenPauseMenu(const FInputActionValue& Value)
{
	PauseMenu->AddToViewport();

	DisableInput(this);

	SetInputMode(InputModeUIOnly);

	SetShowMouseCursor(true);

	SetPause(true);
}

void AMyPlayerController::OnPlayerDeath()
{
	if (!IsDying)
	{
		IsDying = true;

		DisableInput(this);

		PlayerCameraManager->StartCameraFade(0, 1, DeathFadeInTime, FColor::Black, true, true);

		UGameplayStatics::PlaySound2D(GetWorld(), DyingSound, DyingSoundVolume);

		if (MyPlayerState->GetCurrentlyHeldItem())
		{
			MyPlayerState->GetCurrentlyHeldItem()->ThrowItem(FVector::Zero());

			MyPlayerState->RemoveCurrentlyHeldItem();
		}

		FTimerHandle Handle;

		GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyPlayerController::OnCheckpointRestart, 4, false);
	}
}

void AMyPlayerController::OnPlayerVictory()
{
	DisableInput(this);

	PlayerCameraManager->StartCameraFade(0, 1, VictoryFadeInTime, FColor::Black, true, true);

	FTimerHandle Handle;

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyPlayerController::ChangeToVictoryLevel, VictoryFadeInTime);
}

void AMyPlayerController::ChangeToVictoryLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("Victory"));
}

void AMyPlayerController::OnCheckpointRestart()
{
	IsDying = false;

	PlayerCameraManager->StartCameraFade(1, 0, DeathFadeOutTime, FColor::Black, true, false);

	MyChara->SetActorLocation(MyPlayerState->GetLatestCheckpoint().Position);
	
	SetControlRotation(MyPlayerState->GetLatestCheckpoint().Rotation);

	MyChara->UnCrouch();

	MyChara->GetCharacterMovement()->MaxWalkSpeed = DefaultMaxSpeed;

	EnableInput(this);

	MyGameState->OnCheckpointRestart.Broadcast();
}

void AMyPlayerController::OnPlayerEnterHideSpot(AActor* HideSpot)
{
	SetViewTargetWithBlend(HideSpot, HideSpotCameraBlendTime);
}

void AMyPlayerController::OnPlayerExitHideSpot()
{
	SetViewTargetWithBlend(MyChara, HideSpotCameraBlendTime);
}

void AMyPlayerController::OnResumeGame()
{
	PauseMenu->RemoveFromParent();

	EnableInput(this);

	SetInputMode(InputModeGameOnly);

	SetShowMouseCursor(false);

	SetPause(false);
}

void AMyPlayerController::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), this, EQuitPreference::Quit, true);
}
