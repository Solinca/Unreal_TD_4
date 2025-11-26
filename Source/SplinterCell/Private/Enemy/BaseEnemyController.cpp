#include "Enemy/BaseEnemyController.h"
#include "Interfaces/Groupable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyGameStateBase.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"

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

	EnemyPawn = Cast<ABaseEnemy>(GetPawn());

	StartingLocation = EnemyPawn->GetActorLocation();

	Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->OnCheckpointRestart.AddUniqueDynamic(this, &ABaseEnemyController::OnCheckpointRestart);
}

void ABaseEnemyController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);

	if (!Stimulus.IsActive())
	{
		return;
	}

	if (SenseClass == UAISense_Sight::StaticClass())
	{
		if (GetBlackboardComponent()->GetValueAsEnum(FName("EnemyState")) != (uint8)EENEMY_STATE::ALERTED && Actor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(Actor) == ECHARACTER_GROUP::PLAYER)
		{
			GetBlackboardComponent()->SetValueAsEnum(FName("EnemyState"), (uint8)EENEMY_STATE::ALERTED);

			EnemyPawn->TriggerAlertVFX();

			EnemyPawn->SetPlayerCatchSpeed();
		}
	}
	else if (SenseClass == UAISense_Hearing::StaticClass())
	{
		if (GetBlackboardComponent()->GetValueAsEnum(FName("EnemyState")) != (uint8)EENEMY_STATE::ALERTED)
		{
			GetBlackboardComponent()->SetValueAsEnum(FName("EnemyState"), (uint8)EENEMY_STATE::SUSPICIOUS);

			GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), Stimulus.StimulusLocation);

			EnemyPawn->TriggerSuspicionVFX();
		}
	}
}

void ABaseEnemyController::OnCheckpointRestart()
{
	EnemyPawn->SetActorLocation(StartingLocation);

	EnemyPawn->ResetSpeed();

	EnemyPawn->ResetPatrolIndex();

	GetBlackboardComponent()->SetValueAsEnum(FName("EnemyState"), (uint8)EENEMY_STATE::CALM);

	GetBlackboardComponent()->ClearValue(FName("TargetLocation"));
}
