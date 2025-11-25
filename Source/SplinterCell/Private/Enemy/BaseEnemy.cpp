#include "Enemy/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	AlertVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Alert VFX");

	AlertVFXComponent->SetupAttachment(RootComponent);

	SuspicionVFXComponent = CreateDefaultSubobject<UNiagaraComponent>("Suspicion VFX");

	SuspicionVFXComponent->SetupAttachment(RootComponent);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	MyGameState = Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()));

	StartingSpeed = GetCharacterMovement()->MaxWalkSpeed;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnComponentHit);
}

void ABaseEnemy::OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		MyGameState->OnPlayerDeath.Broadcast();
	}
}

FVector ABaseEnemy::GetNextPatrolPointLocation()
{
	if (PatrolPoints.Num() > 0)
	{
		PatrolIndex = (PatrolIndex + 1) % PatrolPoints.Num();

		return PatrolPoints[PatrolIndex]->GetActorLocation();
	}

	return GetActorLocation();
}

void ABaseEnemy::ResetPatrolIndex()
{
	PatrolIndex = 0;
}

void ABaseEnemy::SetPlayerCatchSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = PlayerCatchSpeed;
}

void ABaseEnemy::ResetSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = StartingSpeed;
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

