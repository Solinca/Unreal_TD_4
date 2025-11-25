#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckIsAtLocation.generated.h"

UCLASS()
class SPLINTERCELL_API UBTDecorator_CheckIsAtLocation : public UBTDecorator
{
	GENERATED_BODY()

private:
	FDelegateHandle Handle;
	
protected:
	UBTDecorator_CheckIsAtLocation();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	EBlackboardNotificationResult OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

	UPROPERTY(EditAnywhere, Category = "Keys")
	FBlackboardKeySelector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Condition")
	float MaxDistance;
};
