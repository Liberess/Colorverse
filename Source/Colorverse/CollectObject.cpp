#include "CollectObject.h"

#include "InventoryManager.h"

ACollectObject::ACollectObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> _ItemMesh(
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (_ItemMesh.Succeeded())
	{
		ItemMesh->SetStaticMesh(_ItemMesh.Object);
		ItemMesh->SetCollisionProfileName("Trigger");
		//ItemMesh->SetupAttachment(RootComponent);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/ItemDatas/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDataTable = DataTable.Object;
}

void ACollectObject::Interact_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, TEXT("collectObject interact"));

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	check(InvenMgr);
	InvenMgr->AddInventoryItem(ItemData);
	Destroy();
}

void ACollectObject::BeginPlay()
{
	Super::BeginPlay();
	
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
