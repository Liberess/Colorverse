#include "CollectObject.h"
#include "InventoryManager.h"

ACollectObject::ACollectObject()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetCollisionProfileName("Trigger");
	StaticMesh->SetupAttachment(DefaultRoot);
}

void ACollectObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACollectObject::SetColorIntensity(int amount)
{
	
}

void ACollectObject::SetBaseTexture(UTexture2D* texture)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan,
		FString::Printf(TEXT("%s"), *texture->GetName()));
	PaintingMatInst->SetTextureParameterValue("BaseTexture", texture);
}

FLinearColor ACollectObject::GetPaintedColor()
{
	FLinearColor currentColor;
	PaintingMatInst->GetVectorParameterValue(FName(TEXT("OverlayColor")), currentColor);
	return currentColor;
}
