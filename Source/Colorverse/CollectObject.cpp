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

	IsInteractable = true;
	CurrentScale = FVector::ZeroVector;

	/*ObjMatInst = UMaterialInstanceDynamic::Create(ObjMatTemplate, this);
	StaticMesh->SetMaterial(0, ObjMatInst);*/

	if(IsValid(ItemDT) && !ItemName.IsEqual(""))
	{
		ItemData = *(ItemDT->FindRow<FItem>(ItemName, ""));
		InteractWidgetDisplayTxt = ItemData.Name.ToString();
	}
}

void ACollectObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACollectObject::OnInteract_Implementation()
{
	IIInteractable::OnInteract_Implementation();
	
	//Super::OnInteract_Implementation();
	//Super::Interact_Implementation();
	if(ItemData.bIsValid)
	{
		UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
		InvenMgr->AddInventoryItem(ItemData);
	}
}

void ACollectObject::SetCollectObjectData(FName _itemName)
{
	ItemData = *(ItemDT->FindRow<FItem>(_itemName, ""));
	InteractWidgetDisplayTxt = ItemData.Name.ToString();
}
