#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Items/GrabbableItem.h"
#include "Camera/CameraComponent.h"
#include "MyPlayerState.generated.h"

USTRUCT()
struct FCheckpointInfo
{
	GENERATED_BODY()

	FVector Position;

	FRotator Rotation;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerEnterHideSpotSignature, AActor*, HideSpot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerExitHideSpotSignature);

UCLASS()
class SPLINTERCELL_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	TArray<AGrabbableItem*> NearPlayerItems;

	AGrabbableItem* CurrentlyHeldItem = nullptr;

	FCheckpointInfo LatestCheckpoint;

	FVector PlayerCheckpointPosition;

	FRotator PlayerCheckpointRotation;
	
public:
	void RegisterNearItem(AGrabbableItem* item);

	void RemoveNearItem(AGrabbableItem* item);

	bool GrabNearestItem();

	AGrabbableItem* GetCurrentlyHeldItem();

	void RemoveCurrentlyHeldItem();

	void RegisterNewCheckpoint(FVector CheckpointPosition, FRotator CheckpointRotation);

	FCheckpointInfo GetLatestCheckpoint();

	UPROPERTY(EditDefaultsOnly, BlueprintCallable, Category = "Events")
	FOnPlayerEnterHideSpotSignature OnPlayerEnterHideSpot;

	UPROPERTY(EditDefaultsOnly, BlueprintCallable, Category = "Events")
	FOnPlayerExitHideSpotSignature OnPlayerExitHideSpot;
};
