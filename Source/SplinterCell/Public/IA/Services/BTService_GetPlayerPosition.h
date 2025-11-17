#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetPlayerPosition.generated.h"

UCLASS()
class SPLINTERCELL_API UBTService_GetPlayerPosition : public UBTService
{
	GENERATED_BODY()
	
protected:
	UBTService_GetPlayerPosition();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocation;
};
