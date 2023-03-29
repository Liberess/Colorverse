#include "InteractObject.h"
#include "ColorverseCharacter.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Green, text);

AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCol->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCol->SetCollisionProfileName(TEXT("Trigger"));
	BoxCol->SetupAttachment(DefaultRoot);

	BoxCol->OnComponentBeginOverlap.AddDynamic(this, &AInteractObject::OnOverlapBegin);
	BoxCol->OnComponentEndOverlap.AddDynamic(this, &AInteractObject::OnOverlapEnd);
}

void AInteractObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		static AColorverseCharacter* Character = Cast<AColorverseCharacter>(OtherActor);
		if(IsValid(Character))
			OnEnter();
	}
}

void AInteractObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
	//Print(1.0f, TEXT("InteractObject::OnEnter"));
}

void AInteractObject::OnInteract()
{
	Interact();
}

void AInteractObject::Interact_Implementation()
{
	//Print(1.0f, TEXT("InteractObject::Interact"));
}

void AInteractObject::OnExit()
{
	//Print(1.0f, TEXT("InteractObject::OnExit"));
}
