#include "Statue.h"

void AStatue::BeginPlay()
{
	Super::BeginPlay();

	bIsUnlock = false;
	IsInteractable = true;
}

void AStatue::OnEnter_Implementation()
{
	
}

void AStatue::OnInteract_Implementation()
{
	if(bIsUnlock || !IsInteractable)
		return;

	bIsUnlock = true;
	IsInteractable = false;
	StaticMesh->SetRenderCustomDepth(false);

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange,
		TEXT("AStatue::OnInteract 실제 효과 적용 필요"));
}

void AStatue::OnExit_Implementation()
{
	
}