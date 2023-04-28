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

	if(IsValid(ItemDT))
	{
		FString RowStr = "Item_";
		RowStr.Append(FString::FromInt(ItemID));
		ItemData = *(ItemDT->FindRow<FItem>(FName(*RowStr), ""));
		WoodStickData = *(ItemDT->FindRow<FItem>(FName(TEXT("WoodStick")), ""));
		InteractWidgetDisplayTxt = ItemData.Name.ToString();
	}
	
	TArray<AActor*> tempActors;
	GetAllChildActors(tempActors, true);
	for (auto actor : tempActors)
	{
		if (auto collectObj = Cast<ACollectObject>(actor))
		{
			collectObj->ItemData = ItemData;
			//collectObj->SetCollectObjectData(SeparatedItemName);
			CollectObjects.Add(collectObj);
		}
	}

	for (int i = 0; i < CollectObjects.Num(); i++)
	{
		FTimerHandle newHandle;
		SpawnTimerHandles.Add(newHandle);
	}
}

void AFruitTree::Interact_Implementation()
{
	Super::Interact_Implementation();

	static UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();

	//흔들리는 Animation 출력

	//열려있는 사과 획득
	for (int i = 0; i < CollectObjects.Num(); i++)
	{
		if (!CollectObjects[i]->IsHidden())
		{
			//이제 달린 사과가 없으니 상호작용 끔
			if(i == CollectObjects.Num() - 1)
				IsInteractable = false;
				
			SetActiveCollectObject(false, i);
			GetWorldTimerManager().SetTimer(SpawnTimerHandles[i], FTimerDelegate::CreateLambda([i, this]
			{
				SetActiveCollectObject(true, i);
			}), SpawnDelayTime, false);
			
			int Rand = FMath::RandRange(1, CollectObjects.Num());

			for(int j = 0; j < Rand; j++)
				InvenMgr->AddInventoryItem(ItemData);
			
			break;
		}
	}

	//나뭇가지 획득
	int Rand = FMath::RandRange(1, MaxWoodStickAcquireAmount);
	WoodStickData.Amount = Rand;
	InvenMgr->AddInventoryItem(WoodStickData);
}

void AFruitTree::SetActiveCollectObject(bool active, int index)
{
	if (index < 0 || index >= CollectObjects.Num())
		return;

	if(active)
	{
		CollectObjects[index]->bIsGrown = true;
		CollectObjects[index]->TargetScale = FVector::OneVector;
	}
	else
	{
		CollectObjects[index]->bIsGrown = true;
		CollectObjects[index]->TargetScale = FVector::ZeroVector;
	}

	// active가 true라면 CollectObject를 활성화한다.
	CollectObjects[index]->SetActorHiddenInGame(!active);
	CollectObjects[index]->SetActorEnableCollision(active);
	CollectObjects[index]->SetActorTickEnabled(active);
}
