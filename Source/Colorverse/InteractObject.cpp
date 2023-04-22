#include "InteractObject.h"
#include "ColorArea.h"
#include "ColorverseCharacter.h"
#include "Kismet/GameplayStatics.h"

AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCol->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCol->SetCollisionProfileName(TEXT("Trigger"));
	BoxCol->SetupAttachment(DefaultRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultRoot);

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

void AInteractObject::AddColorAreaEnabledAction()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AColorArea::StaticClass(), FoundActors);
	for (auto& Actor : FoundActors)
	{
		if(AColorArea* ColorArea = Cast<AColorArea>(Actor))
		{
			if(ColorArea->StageName == ParentStageName)
			{
				ColorArea->OnSetEnabledStageInteract.AddDynamic(this, &AInteractObject::SetEnabledInteractable);
				break;
			}
		}
	}
}
