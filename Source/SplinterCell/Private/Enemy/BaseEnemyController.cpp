#include "Enemy/BaseEnemyController.h"
#include "Interfaces/Groupable.h"

ABaseEnemyController::ABaseEnemyController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
}

void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (BaseTree)
	{
		RunBehaviorTree(BaseTree);

		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseEnemyController::OnTargetPerceptionUpdated);
	}
}

void ABaseEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->Implements<UGroupable>())
	{
		if (IGroupable::Execute_GetCharacterGroup(Actor) == ECHARACTER_GROUP::PLAYER)
		{
			GetBlackboardComponent()->SetValueAsEnum(FName("EnemyState"), (uint8) EENEMY_STATE::ALERTED);
		}
	}
}
