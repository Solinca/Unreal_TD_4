#include "Items/ExtractionPoint.h"
#include "Interfaces/Groupable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyGameStateBase.h"

AExtractionPoint::AExtractionPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");

	Box->SetupAttachment(RootComponent);
}

void AExtractionPoint::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AExtractionPoint::OverlapBegin);
}

void AExtractionPoint::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		Cast<AMyGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->OnPlayerVictory.Broadcast();
	}
}
