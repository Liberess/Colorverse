#include "ColorArea.h"
#include "ColorManager.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Cyan, text);

AColorArea::AColorArea()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCol->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCol->SetCollisionProfileName(TEXT("Trigger"));
	BoxCol->SetupAttachment(RootComponent);
}

void AColorArea::BeginPlay()
{
	Super::BeginPlay();
}

void AColorArea::OnEnter()
{
	//Super::OnEnter();
	Print(1.0f, "Enter");
}

void AColorArea::OnInteract()
{
	//Super::OnInteract();
	UColorManager* ColorMgr = GetWorld()->GetSubsystem<UColorManager>();
	check(ColorMgr);
	if(ColorMgr->GetLightAmount(StageName) > 0)
	{
		SetEnabledPostProcess(false);
		IsLightness = true;
		Destroy();
	}
}

void AColorArea::OnExit()
{
	//Super::OnExit();
	Print(1.0f, "Exit");
}

void AColorArea::SetEnabledPostProcess(bool Active)
{
	check(PostVolume);
	PostVolume->bEnabled = Active;
}
