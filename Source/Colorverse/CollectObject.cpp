#include "CollectObject.h"

#include "InventoryManager.h"

ACollectObject::ACollectObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACollectObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACollectObject::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("collectObject interact"));

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr);
	InvenMgr->AddInventoryItem(ItemData);
	Destroy();
}

