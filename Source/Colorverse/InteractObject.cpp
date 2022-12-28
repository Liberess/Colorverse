#include "InteractObject.h"
#include "ColorverseCharacter.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Green, text);

AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &AInteractObject::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AInteractObject::OnOverlapEnd);
}

void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractObject::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		static AColorverseCharacter* Character = Cast<AColorverseCharacter>(OtherActor);
		if(IsValid(Character))
			OnEnter();
	}
}

void AInteractObject::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		static AColorverseCharacter* Character = Cast<AColorverseCharacter>(OtherActor);
		if(IsValid(Character))
			OnExit();
	}
}

void AInteractObject::OnEnter()
{
	Print(1.0f, TEXT("InteractObject::OnEnter"));
}

void AInteractObject::OnInteract()
{
	Print(1.0f, TEXT("InteractObject::OnInteract"));
}

void AInteractObject::OnExit()
{
	Print(1.0f, TEXT("InteractObject::OnExit"));
}
