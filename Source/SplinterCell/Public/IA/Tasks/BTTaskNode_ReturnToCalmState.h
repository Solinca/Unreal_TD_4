#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ReturnToCalmState.generated.h"

UCLASS()
class SPLINTERCELL_API UBTTaskNode_ReturnToCalmState : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	UBTTaskNode_ReturnToCalmState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector EnemyState;
};
