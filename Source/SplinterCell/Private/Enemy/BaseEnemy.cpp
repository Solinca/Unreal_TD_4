#include "Enemy/BaseEnemy.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

TArray<ATargetPoint*> ABaseEnemy::GetPatrolPoints()
{
	return PatrolPoints;
}

