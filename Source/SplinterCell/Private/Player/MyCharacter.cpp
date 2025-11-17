#include "Player/MyCharacter.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(SpringArm);
}

ECHARACTER_GROUP AMyCharacter::GetCharacterGroup_Implementation()
{
	return ECHARACTER_GROUP::PLAYER;
}
