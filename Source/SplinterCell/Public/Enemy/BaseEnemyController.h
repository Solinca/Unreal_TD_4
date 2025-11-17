#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"

UCLASS()
class SPLINTERCELL_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	ABaseEnemyController();
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Behavior Tree")
	TObjectPtr<UBehaviorTree> BaseTree = nullptr;
};
