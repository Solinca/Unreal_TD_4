#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "MyGameStateBase.h"
#include "Items/GrabbableItem.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerController.generated.h"

USTRUCT(BlueprintType)
struct FInputData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	TObjectPtr<UInputAction> Action = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	ETriggerEvent TriggerType;

	UPROPERTY(EditAnywhere, meta = (FunctionReference, PrototypeFunction = "/Script/SplinterCell.MyPlayerController.Prototype_InputAction"))
	FMemberReference ActionName;
};

UCLASS()
class SPLINTERCELL_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	AMyCharacter* MyChara = nullptr;

	AMyGameStateBase* MyGameState = nullptr;

	AMyPlayerState* MyPlayerState = nullptr;

	float DefaultMaxSpeed = 0;

	bool IsAiming = false;

	bool IsDying = false;

#if WITH_EDITOR
	UFUNCTION(BlueprintInternalUseOnly)
	void Prototype_InputAction(const FInputActionValue& Value) {};
#endif

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void SprintStart(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void SprintStop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CrouchStart(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void CrouchStop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Grab(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void AimStart(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void AimStop(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Throw(const FInputActionValue& Value);

	UFUNCTION()
	void OnPlayerDeath();

	UFUNCTION()
	void OnCheckpointRestart();

	UFUNCTION()
	void OnPlayerEnterHideSpot(AActor* HideSpot);

	UFUNCTION()
	void OnPlayerExitHideSpot();
	
protected:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Mapping")
	TObjectPtr<UInputMappingContext> MappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Data")
	TArray<FInputData> InputDatas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Settings")
	float CameraSensitivity = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Settings")
	float PlayerSprintFactor = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Settings")
	float ThrowForce = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound Settings")
	TObjectPtr<USoundBase> DyingSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound Settings")
	float DyingSoundVolume = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fade Settings")
	float HideSpotCameraBlendTime = 0.33f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fade Settings")
	float DeathFadeInTime = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fade Settings")
	float DeathFadeOutTime = 1;
};
