#include "FruitTree.h"
#include "InventoryManager.h"

AFruitTree::AFruitTree()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/DataTables/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDT = DataTable.Object;

	SetRootComponent(StaticMesh);
	BoxCol->SetupAttachment(StaticMesh);
}

void AFruitTree::BeginPlay()
{
	Super::BeginPlay();

	IsInteractable = true;

	if(IsValid(ItemDT))
	{
		ItemData = *(ItemDT->FindRow<FItem>(ItemName, ""));
		ItemData.Amount = FruitMeshes.Num();
		WoodStickData = *(ItemDT->FindRow<FItem>(FName(TEXT("WoodStick")), ""));
		InteractWidgetDisplayTxt = ItemData.Name.ToString();
	}
}

void AFruitTree::OnInteract_Implementation()
{
	IIInteractable::OnInteract_Implementation();

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	
	//흔들리는 Animation 출력

	//열려있는 열매 획득
	if(CanAcquireFruit)
	{
		CanAcquireFruit = false;
		SetActiveCollectObject(false);
		
		InvenMgr->AddInventoryItem(ItemData);
	
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this]
		{
			CanAcquireFruit = true;
			SetActiveCollectObject(true);
		}), FruitSpawnDelayTime, false);
	}

	//나뭇가지 획득
	int Rand = FMath::RandRange(1, MaxWoodStickAcquireAmount);
	WoodStickData.Amount = Rand;
	InvenMgr->AddInventoryItem(WoodStickData);
}
