#include "PaintedCollectObject.h"

APaintedCollectObject::APaintedCollectObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/ItemDatas/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDataTable = DataTable.Object;
}

void APaintedCollectObject::BeginPlay()
{
	Super::BeginPlay();

	if(IsColorActive)
	{
		PaintingMatInst->SetTextureParameterValue("BaseTexture", ActiveTexture);
	}
	else
	{
		PaintingMatInst->SetTextureParameterValue("BaseTexture", InActiveTexture);
	}

	/*GetWorldTimerManager().SetTimer(SpawnTimerHandles[0], this,
		&APaintedCollectObject::SpawnCollectObject, SpawnDelayTime, false, 0.0f);*/

	for(int i = 0; i < CollectObjects.Num(); i++)
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandles[i], FTimerDelegate::CreateLambda([i, this]
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("g"));
			SpawnCollectObjectByIndex(i);
		}), SpawnDelayTime, false, 0.0f);
	}
	
	try
	{
		check(ItemDataTable);
		FString RowStr = "Item_";
		RowStr.Append(FString::FromInt(ItemID));
		ItemData = *(ItemDataTable->FindRow<FItem>(FName(*RowStr), ""));
		InteractWidgetDisplayTxt = ItemData.Name.ToString();
	}
	catch (...)
	{
		
	}
}

void APaintedCollectObject::PaintToObject_Implementation()
{
	if(IsColorActive)
		return;
	
	++PaintedCount;

	if(PaintedCount >= NeedsPaintedCount)
	{
		IsColorActive = true;
		PaintingMatInst->SetTextureParameterValue("BaseTexture", ActiveTexture);
	}
}

void APaintedCollectObject::SpawnCollectObject_Implementation()
{
	for(auto& CollectObj : CollectObjects)
	{
		if(CollectObj->IsHidden())
		{
			CollectObj->SetActorHiddenInGame(true);
			CollectObj->SetActorEnableCollision(true);
			CollectObj->SetActorTickEnabled(true);
			break;
		}
	}
}

void APaintedCollectObject::SpawnCollectObjectByIndex(int ObjectIndex)
{
	if(ObjectIndex < 0 || ObjectIndex >= CollectObjects.Num())
		return;
}
