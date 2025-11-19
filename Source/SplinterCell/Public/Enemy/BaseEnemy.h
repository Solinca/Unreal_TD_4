#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/Groupable.h"
#include "NiagaraComponent.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SPLINTERCELL_API ABaseEnemy : public ACharacter, public IGroupable
{
	GENERATED_BODY()

protected:
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float PlayerCatchSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraComponent> AlertVFXComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TObjectPtr<UNiagaraComponent> SuspicionVFXComponent = nullptr;

public:
	TArray<ATargetPoint*> GetPatrolPoints();

	void SetPlayerCatchSpeed();

	void TriggerAlertVFX();

	void TriggerSuspicionVFX();

	virtual ECHARACTER_GROUP GetCharacterGroup_Implementation() override;
};
