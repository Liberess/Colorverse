#include "InventoryManager.h"
#include "ColorverseWorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "ColorverseCharacter.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Yellow, text);

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
	for(int i = 0; i < 21; i++)
		InventoryArray.Add(FItem());
	
	for(int i = 0; i < 2; i++)
		MakerArray.Add(FItem());

	for(int i = 0; i < 1; i++)
		StatueArray.Add(FItem());

	const FSoftClassPath InventoryRef(TEXT("/Game/UI/BP_InventoryWidget.BP_InventoryWidget_C"));
	if(UClass* WidgetClass = InventoryRef.TryLoadClass<UInventoryWidget>())
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), WidgetClass));
		InventoryWidget->CreateContainer(InventoryArray.Num());
	}

	const FSoftClassPath MakerRef(TEXT("/Game/UI/BP_MakerWidget.BP_MakerWidget_C"));
	if(UClass* WidgetClass = MakerRef.TryLoadClass<UMakerWidget>())
	{
		MakerWidget = Cast<UMakerWidget>(CreateWidget(GetWorld(), WidgetClass));
		MakerWidget->CreateContainer(MakerArray.Num());
	}

	const FSoftClassPath StatueRef(TEXT("/Game/UI/BP_StatueWidget.BP_StatueWidget_C"));
	if(UClass* WidgetClass = StatueRef.TryLoadClass<UStatueWidget>())
	{
		StatueWidget = Cast<UStatueWidget>(CreateWidget(GetWorld(), WidgetClass));
		StatueWidget->CreateContainer(StatueArray.Num());
	}

	const FSoftClassPath HUDRef(TEXT("/Game/UI/BP_HUD.BP_HUD_C"));
	if(UClass* WidgetClass = HUDRef.TryLoadClass<UHUDWidget>())
	{
		HUDWidget = Cast<UHUDWidget>(CreateWidget(GetWorld(), WidgetClass));
		HUDWidget->InitializedHUD();
		HUDWidget->AddToViewport();
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStatue::StaticClass(), FoundActors);
	for (auto& Actor : FoundActors)
		Statues.Add(Cast<AStatue>(Actor));

	Statues.Sort([&](const AStatue& s1, const AStatue& s2)
	{
		return s1.StatueIndex < s2.StatueIndex;
	});
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
	}
}

void UInventoryManager::SetMakerUI(bool IsActive, bool IsFlip)
{
	if(!IsValid(MakerWidget) || IsActive && bIsStatueOpen)
		return;;

	if(IsFlip)
	{
		bIsMakerOpen = !bIsMakerOpen;
	}
	else
	{
		if(bIsMakerOpen && bIsMakerOpen == IsActive)
			return;

		bIsMakerOpen = IsActive;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(bIsMakerOpen)
	{
		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetWidgetToFocus(MakerWidget->TakeWidget());
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputModeGameAndUI.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputModeGameAndUI);
		PlayerController->SetShowMouseCursor(true);
		MakerWidget->AddToViewport();
		MakerWidget->PlayAnimation(MakerWidget->MakerShowAnim);
		UpdateMaker();
	}
	else
	{
		for(int i = 0; i < MakerArray.Num(); i++)
		{
			if(MakerArray[i].bIsValid)
			{
				AddInventoryItem(MakerArray[i]);
				MakerArray[i] = FItem();
			}
		}

		UpdateMaker();
		UpdateInventory();
		
		const FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(false);
		MakerWidget->RemoveFromParent();
	}
}

void UInventoryManager::SetStatueUI(bool IsActive, bool IsUnlockPanel)
{
	if(!IsValid(StatueWidget))
		return;

	bIsStatueOpen = IsActive;
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(IsActive)
	{
		FInputModeGameAndUI InputModeGameAndUI;
		InputModeGameAndUI.SetWidgetToFocus(StatueWidget->TakeWidget());
		InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputModeGameAndUI.SetHideCursorDuringCapture(true);
		PlayerController->SetInputMode(InputModeGameAndUI);
		PlayerController->SetShowMouseCursor(true);
		StatueWidget->AddToViewport();
		StatueWidget->SetActiveCanvasPanel(IsUnlockPanel);
		//StatueWidget->PlayAnimation(StatueWidget->MakerShowAnim);
		UpdateStatue();
	}
	else
	{
		for(int i = 0; i < StatueArray.Num(); i++)
		{
			if(StatueArray[i].bIsValid)
			{
				AddInventoryItem(StatueArray[i]);
				StatueArray[i] = FItem();
			}
		}

		UpdateStatue();
		UpdateInventory();
		
		const FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(false);
		StatueWidget->RemoveFromParent();
	}
}

void UInventoryManager::UpdateInventory()
{
	InventoryWidget->UpdateContainer(InventoryArray);
}

void UInventoryManager::UpdateMaker()
{
	MakerWidget->UpdateContainer(MakerArray);
}

void UInventoryManager::UpdateStatue()
{
	StatueWidget->UpdateContainer(StatueArray);
}

void UInventoryManager::AddInventoryItem(const FItem& Item)
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

	HUDWidget->AddItemLog(Item);

	/*if(ItemAcquiredWidgetClass)
	{
		UItemAcquiredWidget* AcquiredWidget = Cast<UItemAcquiredWidget>(ItemAcquiredWidgetPool->GetOrCreateWidget(GetWorld(), ItemAcquiredWidgetClass));
		if (AcquiredWidget)
		{
			AcquiredWidget->AddToViewport();
			AcquiredWidget->ShowItemAcquired(Item);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, AcquiredWidget]()
			{
				AcquiredWidget->SetVisibility(ESlateVisibility::Collapsed);
				ItemAcquiredWidgetPool->ReleaseWidget(AcquiredWidget);
			}, 3.0f, false);
		}
	}*/
}

void UInventoryManager::UseInventoryItem(FItem Item)
{
	static int Index = 0;
	if(GetInventoryItemByName(Item.Name, Index))
	{
		InventoryArray[Index].Amount -= 1;
		
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
		if(InventoryArray[i].Name.EqualTo(Name))
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
	
	try
	{
		const FString SrcItemName = SrcItem.Name.ToString();
		const FString DestItemName = DestItem.Name.ToString();

		const FCombine* CombineRule = CombineDataTable->FindRow<FCombine>(FName(SrcItemName + DestItemName), "");
		if(CombineRule != nullptr)
		{
			if(SrcItem.Amount - 1 > 0)
				--SrcItem.Amount;
			else
				SrcItem = EmptyItem;

			if(DestItem.Amount - 1 > 0)
				--DestItem.Amount;
			else
				DestItem = EmptyItem;

			const FItem Item = *(ItemDataTable->FindRow<FItem>(FName(CombineRule->ResultItemName.ToString()), ""));
			AddInventoryItem(Item);
			UpdateMaker();
		}
	}
	catch (...)
	{
		
	}
}

void UInventoryManager::SacrificeItems(ESacrificeType SacrificeType)
{
	const FItem& EmptyItem = FItem();
	
	// 제물로 바쳐진 아이템이 "해금"하는데 사용되는 것이라면
	if(SacrificeType == ESacrificeType::Unlock)
	{
		for(auto& Item : StatueArray)
		{
			if(!Item.bIsValid && Item.CombineType != EItemCombineType::SacrificeUnlock)
				continue;
			
			int MergeValue = Item.Amount + CurrentStatue->UnlockCount;
			if(MergeValue >= CurrentStatue->UnlockCapacity)
			{
				int DecreaseAmount = CurrentStatue->UnlockCapacity - CurrentStatue->UnlockCount;
				CurrentStatue->UnlockCount += DecreaseAmount;
				
				Item.Amount -= DecreaseAmount;
				if(Item.Amount <= 0)
					Item = EmptyItem;

				if(CurrentStatue->UnlockCount >= CurrentStatue->UnlockCapacity)
				{
					if(Item.bIsValid)
					{
						AddInventoryItem(Item);
						Item = EmptyItem;
					}
					break;
				}
			}
			else
			{
				CurrentStatue->UnlockCount += Item.Amount;
				Item = EmptyItem;
			}
		}

		if(CurrentStatue->UnlockCount >= CurrentStatue->UnlockCapacity)
		{
			CurrentStatue->UnlockCount = CurrentStatue->UnlockCapacity;
			CurrentStatue->bIsUnlockComplete = true;
			CurrentStatue->ActiveUnlockEffect();
			StatueWidget->SetActiveCanvasPanel(false);
			
			// 플레이어 속성 공격 활성화
			AColorverseCharacter* Player = Cast<AColorverseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			// 플레이어 컨트롤러와 캐릭터가 null 이 아닌지 확인
			if (Player != nullptr)
			{
				Player->GetCombatSystem()->SetElementBuff((int)CurrentStatue->StatueColor);
			}
		}
	}
	else
	{
		for(auto& Item : StatueArray)
		{
			if(!Item.bIsValid && Item.CombineType != EItemCombineType::SacrificeRecovery)
				continue;
			
			int MergeValue = (Item.Amount * Item.RecoveryAmount) + CurrentStatue->RecoveryAmount;
			if(MergeValue >= CurrentStatue->RecoveryCapacity)
			{
				int DecreaseAmount = CurrentStatue->RecoveryCapacity - CurrentStatue->RecoveryAmount;
				CurrentStatue->RecoveryAmount += DecreaseAmount;
				
				Item.Amount -= (DecreaseAmount / Item.RecoveryAmount);
				if(Item.Amount <= 0)
					Item = EmptyItem;

				if(CurrentStatue->RecoveryAmount >= CurrentStatue->RecoveryCapacity)
				{
					if(Item.bIsValid)
					{
						AddInventoryItem(Item);
						Item = EmptyItem;
					}
					break;
				}
			}
			else
			{
				CurrentStatue->RecoveryAmount += Item.Amount * Item.RecoveryAmount;
				Item = EmptyItem;
			}
		}

		if(CurrentStatue->RecoveryAmount >= CurrentStatue->RecoveryCapacity)
		{
			CurrentStatue->RecoveryAmount = CurrentStatue->RecoveryCapacity;
			CurrentStatue->bIsRecoveryComplete = true;
		}
	}

	StatueWidget->UpdateStatueUI(CurrentStatue);
	UpdateStatue();
}

void UInventoryManager::IncreaseStatueColorRecoveryProgress(ECombineColors SacrificeColor, float Amount)
{
	int index = static_cast<int>(SacrificeColor);
	Statues[index]->WorldRecoveryAmount += Amount;

	if(Statues[index]->WorldRecoveryAmount >= Statues[index]->WorldRecoveryCapacity)
	{
		Statues[index]->WorldRecoveryAmount = Statues[index]->WorldRecoveryCapacity;
		Statues[index]->bIsWorldMineColorRecoveryComplete = true;
	}
}

void UInventoryManager::UpdateStatueUI()
{
	if(IsValid(CurrentStatue))
		StatueWidget->UpdateStatueUI(CurrentStatue);
}
