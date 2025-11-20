#include "Items/GrabbableItem.h"
#include "Interfaces/Groupable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MyPlayerState.h"

AGrabbableItem::AGrabbableItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	Mesh->SetupAttachment(RootComponent);

	Sphere = CreateDefaultSubobject<USphereComponent>("Collider");

	Sphere->SetupAttachment(Mesh);
}

void AGrabbableItem::BeginPlay()
{
	Super::BeginPlay();

	StartingLocation = GetActorLocation();
	StartingRotation = GetActorRotation();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGrabbableItem::OverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AGrabbableItem::OverlapEnd);
}

void AGrabbableItem::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		Cast<AMyPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->RegisterNearItem(this);
	}
}

void AGrabbableItem::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->Implements<UGroupable>() && IGroupable::Execute_GetCharacterGroup(OtherActor) == ECHARACTER_GROUP::PLAYER)
	{
		Cast<AMyPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->RemoveNearItem(this);
	}
}

void AGrabbableItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Mesh->SetVisibility(false, true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorld()->GetTimerManager().SetTimer(Handle, this, &AGrabbableItem::RespawnAfterTime, RespawnTime, false);

	Mesh->OnComponentHit.RemoveDynamic(this, &AGrabbableItem::OnHit);
}

void AGrabbableItem::AttachToPlayerHand(USceneComponent* PlayerMesh, FName SocketName)
{
	AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);

	Mesh->OnComponentHit.AddDynamic(this, &AGrabbableItem::OnHit);
}

void AGrabbableItem::ThrowItem()
{
	Mesh->SetSimulatePhysics(true);

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// Add Force
}

void AGrabbableItem::RespawnAfterTime()
{
	Mesh->SetVisibility(true, true);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Mesh->SetSimulatePhysics(false);

	SetActorRotation(StartingRotation);
	SetActorLocation(StartingLocation);
}
