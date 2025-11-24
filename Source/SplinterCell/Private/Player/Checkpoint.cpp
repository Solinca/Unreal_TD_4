#include "Player/Checkpoint.h"
#include "Interfaces/Groupable.h"
#include "Kismet/GameplayStatics.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Collider");

	Box->SetupAttachment(RootComponent);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	MyPlayerState = Cast<AMyPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACheckpoint::OverlapBegin);
}

void ACheckpoint::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		MyPlayerState->RegisterNewCheckpoint(GetActorLocation(), GetActorRotation());
	}
}

