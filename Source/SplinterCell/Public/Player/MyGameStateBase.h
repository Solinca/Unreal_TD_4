#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckpointRestartSignature);

UCLASS()
class SPLINTERCELL_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDeathSignature OnPlayerDeath;

	UPROPERTY(BlueprintAssignable)
	FOnCheckpointRestartSignature OnCheckpointRestart;
};
