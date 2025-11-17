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

