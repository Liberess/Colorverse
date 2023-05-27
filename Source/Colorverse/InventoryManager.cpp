#include "InventoryManager.h"

#include "ColorverseCharacter.h"
#include "ColorverseWorldSettings.h"
#include "Kismet/GameplayStatics.h"

bool UInventoryManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!Super::ShouldCreateSubsystem(Outer))
		return false;

	const UWorld* WorldOuter = Cast<UWorld>(Outer);
	if (IsValid(WorldOuter))
	{
		AColorverseWorldSettings* WorldSettings = Cast<AColorverseWorldSettings>(WorldOuter->GetWorldSettings());
		if (IsValid(WorldSettings))
			return WorldSettings->bUseInventoryManager;
	}

	return false;
}

UInventoryManager::UInventoryManager()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CombineDT(TEXT("/Game/DataTables/DT_Combine"));
	if (CombineDT.Succeeded())
		CombineDataTable = CombineDT.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDT(TEXT("/Game/DataTables/DT_ItemData"));
	if (ItemDT.Succeeded())
		ItemDataTable = ItemDT.Object;
}

void UInventoryManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInventoryManager::InitializeManager()
{
	for(int i = 0; i < 30; i++)
		InventoryArray.Add(FItem());
	
	for(int i = 0; i < 2; i++)
		MakerArray.Add(FItem());
	
	const FSoftClassPath InventoryRef(TEXT("/Game/UI/BP_InventoryWidget.BP_InventoryWidget_C"));
	if(UClass* WidgetClass = InventoryRef.TryLoadClass<UInventoryWidget>())
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), WidgetClass));
		InventoryWidget->CreateContainer(InventoryArray.Num());
	}

	const FSoftClassPath HUDRef(TEXT("/Game/UI/BP_HUD.BP_HUD_C"));
	if(UClass* WidgetClass = HUDRef.TryLoadClass<UHUDWidget>())
	{
		HUDWidget = Cast<UHUDWidget>(CreateWidget(GetWorld(), WidgetClass));
		HUDWidget->InitializedHUD();
	}
	
	/*TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASanctum::StaticClass(), FoundActors);
	for (auto& Actor : FoundActors)
		Statues.Add(Cast<ASanctum>(Actor));

	Statues.Sort([&](const ASanctum& s1, const ASanctum& s2)
	{
		return s1.StatueIndex < s2.StatueIndex;
	});*/
}

void UInventoryManager::SetInventoryUI(bool IsActive, bool IsFlip)
{
	if(!IsValid(InventoryWidget))
		return;;

	if(IsFlip)
	{
		bIsInventoryOpen = !bIsInventoryOpen;
	}
	else
	{
		if(bIsInventoryOpen && bIsInventoryOpen == IsActive)
			return;

		bIsInventoryOpen = IsActive;
	}
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(bIsInventoryOpen)
	{
		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetWidgetToFocus(InventoryWidget->TakeWidget());
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputModeGameAndUI.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputModeGameAndUI);
		PlayerController->SetShowMouseCursor(true);
		InventoryWidget->AddToViewport();
		InventoryWidget->PlayAnimation(InventoryWidget->InventoryShowAnim);
		UpdateInventory();
	}
	else
	{
		const FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(false);
		InventoryWidget->RemoveFromParent();

		for(int i = 0; i < MakerArray.Num(); i++)
		{
			if(MakerArray[i].bIsValid)
			{
				AddInventoryItem(MakerArray[i], false);
				MakerArray[i] = FItem();
			}
		}

		UpdateMaker();
	}
}

void UInventoryManager::UpdateInventory()
{
	InventoryWidget->UpdateContainer(InventoryArray);
}

void UInventoryManager::UpdateMaker()
{
	InventoryWidget->UpdateMakerContainer(MakerArray);
	UpdateMakerResultUI();
}

void UInventoryManager::UpdateMakerResultUI()
{
	FItem& SrcItem = MakerArray[0];
	FItem& DestItem = MakerArray[1];
	
	if(!SrcItem.bIsValid || !DestItem.bIsValid || CombineDataTable == nullptr)
	{
		InventoryWidget->SetCombineResultUI(FItem(), false);
		return;
	}
	
	TArray<FCombine*> CombineRules;
	FCombine TargetCombine;
	CombineDataTable->GetAllRows("", CombineRules);
	for (auto Combine : CombineRules)
	{
		if(Combine->SrcName.EqualTo(SrcItem.Name)
			&& Combine->DestName.EqualTo(DestItem.Name))
		{
			TargetCombine = *Combine;
			break;
		}
	}

	if(TargetCombine.ResultItemName.EqualTo(FText::FromString("")))
	{
		InventoryWidget->SetCombineResultUI(FItem(), false);
	}
	else
	{
		const FItem Item = *(ItemDataTable->FindRow<FItem>(FName(TargetCombine.ResultItemName.ToString()), ""));
		FName Key = FName(Item.Name.ToString());
		bool IsAlreadyCombine = AlreadyCombineMap.Contains(Key);
		InventoryWidget->SetCombineResultUI(Item, IsAlreadyCombine);
	}
}

void UInventoryManager::AddInventoryItem(const FItem& Item, bool IsShowAcquiredUI)
{
	if(!Item.bIsValid)
		return;
	
	static int Index = 0;
	if(GetInventoryItemByName(Item.Name, Index))
	{
		InventoryArray[Index].Amount += Item.Amount;
	}
	else
	{
		for(int i = 0; i < InventoryArray.Num(); i++)
		{
			if(!InventoryArray[i].bIsValid)
			{
				InventoryArray[i] = Item;
				InventoryArray[i].Amount = Item.Amount;
				break;
			}
		}
	}
	
	UpdateInventory();

	if(IsShowAcquiredUI)
		HUDWidget->AddItemLog(Item);
}

void UInventoryManager::UseInventoryItem(FItem Item)
{
	int Index = 0;
	if(GetInventoryItemByName(Item.Name, Index))
	{
		InventoryArray[Index].Amount -= 1;

		static ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if(AColorverseCharacter* ColorPlayer = Cast<AColorverseCharacter>(Player))
		{
			if(InventoryArray[Index].ConsumeType == EConsumeType::Health)
			{
				ColorPlayer->GetLivingEntity()->CureHealth(InventoryArray[Index].RecoveryAmount);
			}
			else if(InventoryArray[Index].ConsumeType == EConsumeType::Mana)
			{
				PaintAmount += InventoryArray[Index].RecoveryAmount;
				HUDWidget->SetPaintBarPercent(PaintAmount);
			}
			else if(InventoryArray[Index].ConsumeType == EConsumeType::All)
			{
				PaintAmount += InventoryArray[Index].RecoveryAmount;
				HUDWidget->SetPaintBarPercent(PaintAmount);
				ColorPlayer->GetLivingEntity()->CureHealth(InventoryArray[Index].RecoveryAmount);
			}
		}
		
		if(InventoryArray[Index].Amount <= 0)
		{
			Item = FItem();
			InventoryArray[Index] = FItem();
		}

		UpdateInventory();
	}
}

bool UInventoryManager::GetInventoryItemByName(const FText& Name, int& Index)
{
	for(int i = 0; i < InventoryArray.Num(); i++)
	{
		if(InventoryArray[i].bIsValid && InventoryArray[i].Name.EqualTo(Name))
		{
			Index = i;
			return true;
		}
	}

	return false;
}

void UInventoryManager::CombineItems()
{
	FItem& SrcItem = MakerArray[0];
	FItem& DestItem = MakerArray[1];
	
	if(!SrcItem.bIsValid || !DestItem.bIsValid || CombineDataTable == nullptr)
		return;

	const static FItem EmptyItem = FItem();

	TArray<FCombine*> CombineRules;
	CombineDataTable->GetAllRows("", CombineRules);
	for (auto Combine : CombineRules)
	{
		if(Combine->SrcName.EqualTo(SrcItem.Name)
			&& Combine->DestName.EqualTo(DestItem.Name))
		{
			if(SrcItem.Amount - 1 > 0)
				--SrcItem.Amount;
			else
				SrcItem = EmptyItem;

			if(DestItem.Amount - 1 > 0)
				--DestItem.Amount;
			else
				DestItem = EmptyItem;

			const FItem Item = *(ItemDataTable->FindRow<FItem>(FName(Combine->ResultItemName.ToString()), ""));
			AddInventoryItem(Item);
			UpdateMaker();

			FName Key = FName(Item.Name.ToString());
			bool IsAlreadyCombine = AlreadyCombineMap.Contains(Key);
			if(!IsAlreadyCombine)
				AlreadyCombineMap.Add(Key, true);
	
			if(SrcItem.bIsValid && DestItem.bIsValid)
				InventoryWidget->SetCombineResultUI(Item, true);
			
			break;
		}
	}
}
