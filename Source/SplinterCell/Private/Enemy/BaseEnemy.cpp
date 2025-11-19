#include "Enemy/BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	AlertVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Alert VFX");

	AlertVFXComponent->SetupAttachment(RootComponent);

	SuspicionVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Suspicion VFX");

	SuspicionVFXComponent->SetupAttachment(RootComponent);
}

TArray<ATargetPoint*> ABaseEnemy::GetPatrolPoints()
{
	return PatrolPoints;
}

void ABaseEnemy::SetPlayerCatchSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerCatchSpeed;
}

void ABaseEnemy::TriggerAlertVFX()
{
	AlertVFXComponent->Activate();
}

void ABaseEnemy::TriggerSuspicionVFX()
{
	SuspicionVFXComponent->Activate();
}

ECHARACTER_GROUP ABaseEnemy::GetCharacterGroup_Implementation()
{
	return ECHARACTER_GROUP::ENEMY;
}

