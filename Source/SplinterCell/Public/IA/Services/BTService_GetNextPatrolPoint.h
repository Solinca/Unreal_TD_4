#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetNextPatrolPoint.generated.h"

UCLASS()
class SPLINTERCELL_API UBTService_GetNextPatrolPoint : public UBTService
{
	GENERATED_BODY()

private:
	int PatrolIndex = 0;
	
protected:
	UBTService_GetNextPatrolPoint();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocation;
};
