#include "LightObject.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Yellow, text);

ALightObject::ALightObject()
{
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ALightObject::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALightObject::OnOverlapEnd);
}

void ALightObject::BeginPlay()
{
	Super::BeginPlay();
}

void ALightObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightObject::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
		OnEnter();
}

void ALightObject::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
		OnExit();
}

void ALightObject::OnEnter()
{
	Print(1.0f, TEXT("OnEnter"));
}

void ALightObject::OnInteract()
{
	Print(1.0f, TEXT("OnInteract"));
	
}

void ALightObject::OnExit()
{
	Print(1.0f, TEXT("OnExit"));
	
}
