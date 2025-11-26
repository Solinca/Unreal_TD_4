#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGlobalEventSignature);

UCLASS()
class SPLINTERCELL_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGlobalEventSignature OnPlayerDeath;

	UPROPERTY(BlueprintAssignable)
	FGlobalEventSignature OnCheckpointRestart;

	UPROPERTY(BlueprintAssignable)
	FGlobalEventSignature OnPlayerVictory;
};
