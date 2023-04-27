#include "FruitTree.h"
#include "InventoryManager.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Blue, text);

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
	
	TArray<AActor*> tempActors;
	GetAllChildActors(tempActors, true);
	for (auto actor : tempActors)
	{
		if (auto collectObj = Cast<ACollectObject>(actor))
		{
			collectObj->ItemData = ItemData;
			collectObj->SetActorEnableCollision(false);
			collectObj->bIsSeparated = false;
			collectObj->SetInteractable(true);
			collectObj->GlownVelocity = FruitGlownVelocity;
			//collectObj->SetCollectObjectData(SeparatedItemName);
			CollectObjects.Add(collectObj);
		}
	}

	if(IsValid(ItemDT))
	{
		FString RowStr = "Item_";
		RowStr.Append(FString::FromInt(ItemID));
		ItemData = *(ItemDT->FindRow<FItem>(FName(*RowStr), ""));
		ItemData.Amount = CollectObjects.Num();
		WoodStickData = *(ItemDT->FindRow<FItem>(FName(TEXT("WoodStick")), ""));
		InteractWidgetDisplayTxt = ItemData.Name.ToString();
	}
}

void AFruitTree::Interact_Implementation()
{
	Super::Interact_Implementation();

	static UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	Print(1.0f, TEXT("1"));
	//흔들리는 Animation 출력

	//열려있는 사과 획득
	if(CanAcquireFruit)
	{
		CanAcquireFruit = false;
		SetActiveCollectObject(false);
		
		InvenMgr->AddInventoryItem(ItemData);
		Print(1.0f, TEXT("사과 따기"));

		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this]
		{
			CanAcquireFruit = true;
			SetActiveCollectObject(true);
		}), FruitSpawnDelayTime, false);
	}
	
	Print(1.0f, TEXT("나뭇가지 획득"));
	//나뭇가지 획득
	int Rand = FMath::RandRange(1, MaxWoodStickAcquireAmount);
	WoodStickData.Amount = Rand;
	InvenMgr->AddInventoryItem(WoodStickData);
}

void AFruitTree::SetActiveCollectObject(bool active)
{
	for(auto& CollectObj : CollectObjects)
	{
		CollectObj->bIsGrown = true;
		CollectObj->ActiveGlown();
	
		if(active)
			CollectObj->TargetScale = FVector::OneVector;
		else
			CollectObj->TargetScale = FVector::ZeroVector;
	
		// active가 true라면 CollectObject를 활성화한다.
		//CollectObj->SetActorHiddenInGame(!active);
		CollectObj->SetActorEnableCollision(active);
		CollectObj->SetInteractable(active);
		//CollectObj->SetActorTickEnabled(active);
	}
}
