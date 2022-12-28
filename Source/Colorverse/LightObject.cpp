#include "LightObject.h"
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
	Print(1.0f, TEXT("LightObject::OnInteract"));
}

void ALightObject::OnExit()
{
	Print(1.0f, TEXT("LightObject::OnExit"));
}
