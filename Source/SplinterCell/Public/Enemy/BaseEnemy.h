#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/Groupable.h"
#include "NiagaraComponent.h"
#include "Player/MyGameStateBase.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SPLINTERCELL_API ABaseEnemy : public ACharacter, public IGroupable
{
	GENERATED_BODY()

private:
	int PatrolIndex = 0;

	float StartingSpeed;

	AMyGameStateBase* MyGameState = nullptr;

protected:
	ABaseEnemy();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float PlayerCatchSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraComponent> AlertVFXComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraComponent> SuspicionVFXComponent = nullptr;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	FVector GetNextPatrolPointLocation();

	void ResetPatrolIndex();

	void SetPlayerCatchSpeed();

	void ResetSpeed();

	void TriggerAlertVFX();

	void TriggerSuspicionVFX();

	virtual ECHARACTER_GROUP GetCharacterGroup_Implementation() override;
};
