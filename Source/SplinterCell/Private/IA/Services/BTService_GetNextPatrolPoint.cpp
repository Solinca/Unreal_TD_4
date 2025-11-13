#include "IA/Services/BTService_GetNextPatrolPoint.h"
#include "AIController.h"
#include "Enemy/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_GetNextPatrolPoint::UBTService_GetNextPatrolPoint()
{
	NodeName = "Search For Next Patrol Point";
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
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Test");

		PatrolIndex = (PatrolIndex + 1) % BaseEnemy->GetPatrolPoints().Num();

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, BaseEnemy->GetPatrolPoints()[PatrolIndex]->GetActorLocation());
	}
}
