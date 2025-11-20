#include "Player/MyPlayerState.h"

void AMyPlayerState::RegisterNearItem(AGrabbableItem* item)
{
	NearPlayerItems.Add(item);
}

void AMyPlayerState::RemoveNearItem(AGrabbableItem* item)
{
	NearPlayerItems.Remove(item);
}

bool AMyPlayerState::GrabNearestItem()
{
	if (CurrentlyHeldItem)
	{
		return false;
	}

	if (NearPlayerItems.Num() > 0)
	{
		CurrentlyHeldItem = NearPlayerItems[0];

		RemoveNearItem(CurrentlyHeldItem);

		return true;
	}

	return false;
}

AGrabbableItem* AMyPlayerState::GetCurrentlyHeldItem()
{
	return CurrentlyHeldItem;
}

void AMyPlayerState::RemoveCurrentlyHeldItem()
{
	CurrentlyHeldItem = nullptr;
}
