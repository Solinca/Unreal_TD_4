#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Player/MyPlayerState.h"
#include "Checkpoint.generated.h"

UCLASS()
class SPLINTERCELL_API ACheckpoint : public AActor
{
	GENERATED_BODY()

private:
	AMyPlayerState* MyPlayerState = nullptr;
	
protected:	
	ACheckpoint();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> Box = nullptr;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
