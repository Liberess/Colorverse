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

void ALightObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("pre : %d"), ColorMgr->GetLightAmount(EStageName::Stage_1)));
	ColorMgr->SetLightAmount(EStageName::Stage_1, 1);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("now : %d"), ColorMgr->GetLightAmount(EStageName::Stage_1)));
}

void ALightObject::OnExit()
{
	Print(1.0f, TEXT("LightObject::OnExit"));
}
