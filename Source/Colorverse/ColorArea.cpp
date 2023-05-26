#include "ColorArea.h"
#include "ColorManager.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Cyan, text);

AColorArea::AColorArea()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh->SetupAttachment(BoxCol);
	StaticMesh->SetCollisionProfileName("NoCollision");
}

void AColorArea::BeginPlay()
{
	Super::BeginPlay();
}

void AColorArea::OnEnter_Implementation()
{
	//Super::OnEnter();
	//Print(1.0f, "Enter");
}

void AColorArea::OnInteract_Implementation()
{
	//Super::OnInteract();
	UColorManager* ColorMgr = GetWorld()->GetSubsystem<UColorManager>();
	if(ColorMgr != nullptr)
	{
		SetEnabledPostProcess(false);
		IsLightness = true;
		Destroy();
	}
}

void AColorArea::OnExit_Implementation()
{
	//Super::OnExit();
	//Print(1.0f, "Exit");
}

void AColorArea::SetEnabledPostProcess(bool Active)
{
	check(PostVolume);
	PostVolume->bEnabled = Active;
	OnSetEnabledStageInteract.Broadcast(!Active);
}
