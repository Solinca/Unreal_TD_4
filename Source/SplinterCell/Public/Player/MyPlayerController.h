#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MyCharacter.h"
#include "MyPlayerState.h"
#include "Items/GrabbableItem.h"
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

	AMyPlayerState* MyPlayerState = nullptr;

	float DefaultMaxSpeed = 0;

	bool IsAiming = false;

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
};
