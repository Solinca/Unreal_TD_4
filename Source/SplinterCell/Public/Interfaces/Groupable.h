#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Groupable.generated.h"

UENUM(BlueprintType)
enum class ECHARACTER_GROUP : uint8
{
	PLAYER,
	ENEMY
};

UINTERFACE(MinimalAPI)
class UGroupable : public UInterface
{
	GENERATED_BODY()
};

class SPLINTERCELL_API IGroupable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECHARACTER_GROUP GetCharacterGroup();
};
