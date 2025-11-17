#include "Enemy/BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

TArray<ATargetPoint*> ABaseEnemy::GetPatrolPoints()
{
	return PatrolPoints;
}

void ABaseEnemy::SetPlayerCatchSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerCatchSpeed;
}

ECHARACTER_GROUP ABaseEnemy::GetCharacterGroup_Implementation()
{
	return ECHARACTER_GROUP::ENEMY;
}

