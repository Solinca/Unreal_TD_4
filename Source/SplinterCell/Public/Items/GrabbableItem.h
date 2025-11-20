#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GrabbableItem.generated.h"

UCLASS()
class SPLINTERCELL_API AGrabbableItem : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle Handle;

	FVector StartingLocation;
	FRotator StartingRotation;

	void RespawnAfterTime();
	
protected:
	AGrabbableItem();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> Sphere = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float RespawnTime = 5.f;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void AttachToPlayerHand(USceneComponent* PlayerMesh, FName SocketName);

	void ThrowItem();
};
