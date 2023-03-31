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
	InvenMgr->SetStatueUI(true, !bIsUnlock);

	bIsOpenInventoryByStatue = true;
}

void AStatue::OnExit()
{
	//Super::OnExit();
}
