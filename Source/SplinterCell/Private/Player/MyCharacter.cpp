#include "Player/MyCharacter.h"
#include "AISystem.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(SpringArm);
}

UAISense_Sight::EVisibilityResult AMyCharacter::CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData, const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	FHitResult HitResult;

	DrawDebugLine(GetWorld(), Context.ObserverLocation, GetMesh()->GetSocketLocation("head"), FColor::Red);

	bool IsHit = GetWorld()->LineTraceSingleByProfile(HitResult, Context.ObserverLocation, GetMesh()->GetSocketLocation("head"), FName("Pawn"), FCollisionQueryParams("", false, Context.IgnoreActor));

	return (IsHit && HitResult.GetActor() == this) ? UAISense_Sight::EVisibilityResult::Visible : UAISense_Sight::EVisibilityResult::NotVisible;
}

ECHARACTER_GROUP AMyCharacter::GetCharacterGroup_Implementation()
{
	return ECHARACTER_GROUP::PLAYER;
}
