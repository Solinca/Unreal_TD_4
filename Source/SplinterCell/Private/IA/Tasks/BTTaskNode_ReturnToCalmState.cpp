#include "IA/Tasks/BTTaskNode_ReturnToCalmState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/BaseEnemyController.h"

UBTTaskNode_ReturnToCalmState::UBTTaskNode_ReturnToCalmState()
{
	NodeName = "Return To Calm State";
}

EBTNodeResult::Type UBTTaskNode_ReturnToCalmState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8) EENEMY_STATE::CALM);

	return EBTNodeResult::Succeeded;
}
