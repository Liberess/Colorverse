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
	for(int i = 0; i < 25; i++)
		InventoryArray.Add(FItem());
	
	for(int i = 0; i < 2; i++)
		MakerArray.Add(FItem());

	const FSoftClassPath WidgetBPClassRef(TEXT("/Game/UI/BP_InventoryWidget.BP_InventoryWidget_C"));
	if(UClass* WidgetClass = WidgetBPClassRef.TryLoadClass<UInventoryWidget>())
	{
		InventoryWidget = Cast<UInventoryWidget>(CreateWidget(GetWorld(), WidgetClass));
		InventoryWidget->CreateInventory(InventoryArray.Num(), false);
		InventoryWidget->CreateInventory(3, true);
	}
}

void UInventoryManager::SetInventoryUI()
{
	check(InventoryWidget);
	
	bIsInventoryOpen = !bIsInventoryOpen;

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
		UpdateInventory(false);
	}
	else
	{
		const FInputModeGameOnly InputModeGameOnly;
		PlayerController->SetInputMode(InputModeGameOnly);
		PlayerController->SetShowMouseCursor(false);
		InventoryWidget->RemoveFromViewport();
	}
}

void UInventoryManager::UpdateInventory(bool IsMaker)
{
	if(IsMaker)
		InventoryWidget->UpdateInventory(MakerArray, IsMaker);
	else
		InventoryWidget->UpdateInventory(InventoryArray, IsMaker);
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
	
	UpdateInventory(false);
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

		UpdateInventory(false);
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
	if(!MakerArray[0].bIsValid || !MakerArray[1].bIsValid || CombineDataTable == nullptr)
		return;

	try
	{
		const FString SrcItemName = MakerArray[0].Name.ToString();
		const FString DestItemName = MakerArray[1].Name.ToString();

		const FCombine* CombineRule = CombineDataTable->FindRow<FCombine>(FName(SrcItemName + DestItemName), "");
		if(CombineRule != nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow,
				FString::Printf(TEXT("resultItemName = %s"), *CombineRule->ResultItemName.ToString()));
		}
	}
	catch (...)
	{
		
	}
}
