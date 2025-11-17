// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Interfaces/Groupable.h"
#include "BaseEnemy.generated.h"

UCLASS()
class SPLINTERCELL_API ABaseEnemy : public ACharacter, public IGroupable
{
	GENERATED_BODY()

protected:
	ABaseEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol")
	TArray<TObjectPtr<ATargetPoint>> PatrolPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float PlayerCatchSpeed = 1500.f;

public:
	UFUNCTION(BlueprintCallable)
	TArray<ATargetPoint*> GetPatrolPoints();

	void SetPlayerCatchSpeed();

	virtual ECHARACTER_GROUP GetCharacterGroup_Implementation() override;
};
