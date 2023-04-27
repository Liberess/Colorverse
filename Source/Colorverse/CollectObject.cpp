#include "CollectObject.h"
#include "InventoryManager.h"
#include "PaintedCollectObject.h"

ACollectObject::ACollectObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/DataTables/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDT = DataTable.Object;
}

void ACollectObject::BeginPlay()
{
	Super::BeginPlay();

	IsInteractable = false;
	CurrentScale = FVector::ZeroVector;
}

void ACollectObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACollectObject::Interact_Implementation()
{
	//Super::Interact_Implementation();

	if(!bIsSeparated)
		return;

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->AddInventoryItem(ItemData);
}

void ACollectObject::SetCollectObjectData(FName _itemName)
{
	ItemData = *(ItemDT->FindRow<FItem>(_itemName, ""));
	InteractWidgetDisplayTxt = ItemData.Name.ToString();
}
