#include "Statue.h"
#include "InventoryManager.h"

AStatue::AStatue()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();
	StatueIndex = static_cast<int>(StatueColor);
}

void AStatue::OnEnter()
{

}

void AStatue::OnInteract()
{
	Super::OnInteract();

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->SetInventoryUI(true);
	InvenMgr->SetMakerUI(false);
	InvenMgr->SetStatueUI(true, !bIsUnlockComplete);
	InvenMgr->CurrentStatue = this;
	InvenMgr->UpdateStatueUI();
	bIsOpenInventoryByStatue = true;
}

void AStatue::OnExit()
{
	//Super::OnExit();
}
