// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SPLINTERCELL_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

protected:
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

public:
	UFUNCTION(BlueprintCallable)
	TArray<ATargetPoint*> GetPatrolPoints();
};
