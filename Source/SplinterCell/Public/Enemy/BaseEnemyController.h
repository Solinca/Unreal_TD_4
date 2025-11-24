#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy.h"
#include "BaseEnemyController.generated.h"

UENUM(BlueprintType)
enum class EENEMY_STATE : uint8
{
	CALM,
	SUSPICIOUS,
	ALERTED
};

UCLASS()
class SPLINTERCELL_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

private:
	ABaseEnemy* EnemyPawn;

	FVector StartingLocation;

	UFUNCTION()
	void OnCheckpointRestart();

protected:
	ABaseEnemyController();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Behavior Tree")
	TObjectPtr<UBehaviorTree> BaseTree = nullptr;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
