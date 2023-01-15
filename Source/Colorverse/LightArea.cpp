#include "LightArea.h"

ALightArea::ALightArea()
{
	OnActorBeginOverlap.AddDynamic(this, &ALightArea::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALightArea::OnOverlapEnd);
}

void ALightArea::BeginPlay()
{
	Super::BeginPlay();
}

void ALightArea::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		
	}
}

void ALightArea::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		
	}
}
