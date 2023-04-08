#include "PaintedCollectObject.h"
#include "InventoryManager.h"
#include "Engine/TextureRenderTarget2D.h"

APaintedCollectObject::APaintedCollectObject()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/DataTables/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDT = DataTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> PaintComboTable(TEXT("/Game/DataTables/DT_PaintCombo"));
	if (PaintComboTable.Succeeded())
		PaintComboDT = PaintComboTable.Object;
}

void APaintedCollectObject::BeginPlay()
{
	Super::BeginPlay();

	try
	{
		if(IsValid(ItemDT))
		{
			FString RowStr = "Item_";
			RowStr.Append(FString::FromInt(ItemID));
			ItemData = *(ItemDT->FindRow<FItem>(FName(*RowStr), ""));
			InteractWidgetDisplayTxt = ItemData.Name.ToString();
		}

		if(IsValid(PaintComboDT))
		{
			FString str = UEnum::GetDisplayValueAsText(PaintComboColorTag).ToString();
			PaintComboData = *(PaintComboDT->FindRow<FPaintCombo>(FName(*str), ""));
		}
	}
	catch (...)
	{
		
	}

	TArray<AActor*> tempActors;
	GetAllChildActors(tempActors, true);
	for (auto actor : tempActors)
	{
		if (auto collectObj = Cast<ACollectObject>(actor))
		{
			collectObj->PaintComboData = PaintComboData;
			CollectObjects.Add(collectObj);
		}
	}

	for (int i = 0; i < CollectObjects.Num(); i++)
	{
		FTimerHandle newHandle;
		SpawnTimerHandles.Add(newHandle);
	}
}

void APaintedCollectObject::Interact_Implementation()
{
	//Super::Interact_Implementation();
	if(!IsInteractable)
		return;

	if (IsColorActive)
	{
		for (int i = 0; i < CollectObjects.Num(); i++)
		{
			if (!CollectObjects[i]->IsHidden())
			{
				SetActiveCollectObject(false, i);
				GetWorldTimerManager().SetTimer(SpawnTimerHandles[i], FTimerDelegate::CreateLambda([i, this]
				{
					SetActiveCollectObject(true, i);
				}), SpawnDelayTime, false);

				UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
				InvenMgr->AddInventoryItem(ItemData);
				break;
			}
		}
	}
}

void APaintedCollectObject::PaintToObject_Implementation(ECombineColors colorTag, FLinearColor PaintedColor)
{
	if (IsColorActive || !IsInteractable)
		return;

	for (auto& collectObj : CollectObjects)
	{
		if(!collectObj->bIsPaintComplete)
			collectObj->SetPaintedColorAndIntensity(colorTag, PaintedColor);
	}
}

void APaintedCollectObject::SetActiveCollectObject(bool active, int index)
{
	if (index < 0 || index >= CollectObjects.Num())
		return;

	// active가 true라면 CollectObject를 활성화한다.
	CollectObjects[index]->SetActorHiddenInGame(!active);
	CollectObjects[index]->SetActorEnableCollision(active);
	CollectObjects[index]->SetActorTickEnabled(active);
}

void APaintedCollectObject::SetChildCollectObjectTexture(UTexture2D* texture)
{
	for (auto& collectObj : CollectObjects)
		collectObj->SetBaseTexture(texture);
}

void APaintedCollectObject::SetRecoveryColorComplete(ECombineColors color)
{
	IsInteractable = true;
	IsColorActive = true;

	SetChildCollectObjectTexture(ChildActiveTexture);

	UInventoryManager* invenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	invenMgr->IncreaseStatueColorRecoveryProgress(color, 10.0f);

	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]
	{
		GroupMatInst->SetVectorParameterValue("OverlayColor", GroupActiveColor);
		PaintingMatInst->SetTextureParameterValue("BaseTexture", ActiveTexture);
		PaintingMatInst->SetVectorParameterValue("OverlayColor", FColor::White);
		GetWorldTimerManager().ClearTimer(timer);
	}), 2.0f, false);
}



