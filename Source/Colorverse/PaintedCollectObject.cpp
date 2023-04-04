#include "PaintedCollectObject.h"
#include "InventoryManager.h"
#include "Engine/TextureRenderTarget2D.h"

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

	TArray<AActor*> tempActors;
	GetAllChildActors(tempActors, true);
	for (auto actor : tempActors)
	{
		if (auto collectObj = Cast<ACollectObject>(actor))
		{
			CollectObjects.Add(collectObj);

			for(auto& color : VaildPaintColors)
				collectObj->VaildPaintColors.Add(color);
		}
	}

	for (int i = 0; i < CollectObjects.Num(); i++)
	{
		FTimerHandle newHandle;
		SpawnTimerHandles.Add(newHandle);
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

void APaintedCollectObject::Interact_Implementation()
{
	//Super::Interact_Implementation();

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

void APaintedCollectObject::PaintToObject_Implementation(FLinearColor PaintedColor)
{
	if (IsColorActive)
		return;

	for (auto& collectObj : CollectObjects)
	{
		if(collectObj->bIsPaintComplete)
		{
			IsInteractable = true;
			IsColorActive = true;

			SetChildCollectObjectTexture(ChildActiveTexture);

			FTimerHandle timer;
			GetWorldTimerManager().SetTimer(timer, FTimerDelegate::CreateLambda([&]
			{
				GroupMatInst->SetVectorParameterValue("OverlayColor", GroupActiveColor);
				PaintingMatInst->SetTextureParameterValue("BaseTexture", ActiveTexture);
				GetWorldTimerManager().ClearTimer(timer);
			}), 2.0f, false);
		}
		else
		{
			collectObj->SetPaintedColorAndIntensity(PaintedColor);
		}
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
