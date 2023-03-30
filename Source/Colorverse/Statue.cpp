#include "Statue.h"

#include "InventoryManager.h"

AStatue::AStatue()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();
}

void AStatue::OnEnter()
{
	
}

void AStatue::OnInteract()
{
	Super::OnInteract();

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->SetInventoryUI(true);
}

void AStatue::OnExit()
{
	//Super::OnExit();

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("gg"));
	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->SetInventoryUI(false);
}
