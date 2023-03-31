#include "InventoryManager.h"
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
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/ItemDatas/DT_Combine"));
	if (DataTable.Succeeded())
		CombineDataTable = DataTable.Object;
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

	PaintAmountArray = { 0.0f, 0.0f, 0.0f };

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
	if(!IsValid(MakerWidget))
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

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("%d"), IsUnlockPanel));

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

			const int ColorNum = static_cast<int>(CombineRule->CombineColor);
			PaintAmountArray[ColorNum] += GetCombinePaintAmount;
			HUDWidget->SetPaintBarPercent(ColorNum, PaintAmountArray[ColorNum]);
			UpdateMaker();
		}
	}
	catch (...)
	{
		
	}
}
