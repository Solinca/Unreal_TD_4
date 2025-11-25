#include "Items/HideSpot.h"
#include "Interfaces/Groupable.h"
#include "Kismet/GameplayStatics.h"

AHideSpot::AHideSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");

	Box->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(Box);
}

void AHideSpot::BeginPlay()
{
	Super::BeginPlay();

	MyPlayerState = Cast<AMyPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AHideSpot::OverlapBegin);
	Box->OnComponentEndOverlap.AddUniqueDynamic(this, &AHideSpot::OverlapEnd);
}

void AHideSpot::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		MyPlayerState->OnPlayerEnterHideSpot.Broadcast(this);
	}
}

void AHideSpot::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		MyPlayerState->OnPlayerExitHideSpot.Broadcast();
	}
}

