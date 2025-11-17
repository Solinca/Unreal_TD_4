#include "IA/Services/BTService_GetPlayerPosition.h"
#include "AIController.h"
#include "Enemy/BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_GetPlayerPosition::UBTService_GetPlayerPosition()
{
	NodeName = "Get Player Position";
}

void UBTService_GetPlayerPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* Controller = OwnerComp.GetAIOwner();

	if (!Controller)
	{
		return;
	}

	ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(Controller->GetPawn());

	if (!BaseEnemy)
	{
		return;
	}

	ACharacter* MyChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!MyChar)
	{
		return;
	}

	BaseEnemy->SetPlayerCatchSpeed();

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetLocation.SelectedKeyName, MyChar->GetActorLocation());
}
