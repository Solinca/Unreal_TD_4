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
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float PlayerCatchSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<UNiagaraComponent> AlertVFXComponent = nullptr;

public:
	TArray<ATargetPoint*> GetPatrolPoints();

	void SetPlayerCatchSpeed();

	void TriggerAlertVFX();

	virtual ECHARACTER_GROUP GetCharacterGroup_Implementation() override;
};
