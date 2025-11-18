#include "Enemy/BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	AlertVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Alert VFX");

	AlertVFXComponent->SetupAttachment(RootComponent);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
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

ECHARACTER_GROUP ABaseEnemy::GetCharacterGroup_Implementation()
{
	return ECHARACTER_GROUP::ENEMY;
}

