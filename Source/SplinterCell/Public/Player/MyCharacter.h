#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Groupable.h"
#include "Perception/AISightTargetInterface.h"
#include "MyCharacter.generated.h"

UCLASS()
class SPLINTERCELL_API AMyCharacter : public ACharacter, public IGroupable, public IAISightTargetInterface
{
	GENERATED_BODY()

protected:
	AMyCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	FName ItemSocketName = "ItemSocket";

	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;

public:
	virtual ECHARACTER_GROUP GetCharacterGroup_Implementation() override;

	FName GetItemSocketName();
};
