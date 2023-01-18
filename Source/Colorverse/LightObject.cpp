#include "LightObject.h"
#include "ColorManager.h"
#include "ColorverseCharacter.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Yellow, text);

ALightObject::ALightObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALightObject::BeginPlay()
{
	Super::BeginPlay();
}

void ALightObject::OnEnter()
{
	Print(1.0f, TEXT("LightObject::OnEnter"));
}

void ALightObject::OnInteract()
{
	Super::OnInteract();
	Print(1.0f, TEXT("LightObject::OnInteract::Get Light!"));

	UColorManager* ColorMgr = GetWorld()->GetSubsystem<UColorManager>();
	check(ColorMgr);
	ColorMgr->SetLightAmount(StageName, 1);
	Destroy();
}

void ALightObject::OnExit()
{
	Print(1.0f, TEXT("LightObject::OnExit"));
}
