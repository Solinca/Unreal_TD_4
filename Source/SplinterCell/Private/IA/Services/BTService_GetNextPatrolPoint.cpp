#include "IA/Services/BTService_GetNextPatrolPoint.h"
#include "AIController.h"
#include "Enemy/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_GetNextPatrolPoint::UBTService_GetNextPatrolPoint()
{
	NodeName = "Get Next Patrol Point";

	bNotifyBecomeRelevant = true;
}

void UBTService_GetNextPatrolPoint::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller)
	{
		return;
	}

	APawn* Pawn = Controller->GetPawn();

	if (!Pawn)
	{
		return;
	}

	if (ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(Pawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, BaseEnemy->GetNextPatrolPointLocation());
	}
}
