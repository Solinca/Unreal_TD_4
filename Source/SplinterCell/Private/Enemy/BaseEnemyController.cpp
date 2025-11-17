#include "Enemy/BaseEnemyController.h"

ABaseEnemyController::ABaseEnemyController()
{
}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BaseTree);
}
