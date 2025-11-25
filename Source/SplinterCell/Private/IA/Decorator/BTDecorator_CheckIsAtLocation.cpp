#include "IA/Decorator/BTDecorator_CheckIsAtLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTDecorator_CheckIsAtLocation::UBTDecorator_CheckIsAtLocation()
{
	NodeName = "Check Is At Location";

	FlowAbortMode = EBTFlowAbortMode::Self;

	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;

	MaxDistance = 150.f;
}

void UBTDecorator_CheckIsAtLocation::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (const UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		TargetLocation.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		TargetLocation.InvalidateResolvedKey();
	}
}

bool UBTDecorator_CheckIsAtLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller)
	{
		return false;
	}

	APawn* Pawn = Controller->GetPawn();

	if (!Pawn)
	{
		return false;
	}

	return FVector::Dist(Pawn->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(TargetLocation.SelectedKeyName)) < MaxDistance;
}

void UBTDecorator_CheckIsAtLocation::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
    {
		Handle = BlackboardComp->RegisterObserver(TargetLocation.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &UBTDecorator_CheckIsAtLocation::OnBlackboardKeyValueChange));
    }
}

void UBTDecorator_CheckIsAtLocation::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		BlackboardComp->UnregisterObserver(TargetLocation.GetSelectedKeyID(), Handle);
	}
}

EBlackboardNotificationResult UBTDecorator_CheckIsAtLocation::OnBlackboardKeyValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(Blackboard.GetBrainComponent());

    if (!BehaviorComp)
    {
		return EBlackboardNotificationResult::RemoveObserver;
    }

	ConditionalFlowAbort(*BehaviorComp, EBTDecoratorAbortRequest::ConditionResultChanged);

	return EBlackboardNotificationResult::ContinueObserving;
}
