#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Items/GrabbableItem.h"
#include "MyPlayerState.generated.h"

UCLASS()
class SPLINTERCELL_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	TArray<AGrabbableItem*> NearPlayerItems;

	AGrabbableItem* CurrentlyHeldItem = nullptr;
	
public:
	void RegisterNearItem(AGrabbableItem* item);

	void RemoveNearItem(AGrabbableItem* item);

	bool GrabNearestItem();

	AGrabbableItem* GetCurrentlyHeldItem();

	void RemoveCurrentlyHeldItem();
};
