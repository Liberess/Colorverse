#include "CollectObject.h"
#include "ColorModel.h"
#include "InventoryManager.h"

using namespace Liberess;

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

void ACollectObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bIsPaintComplete && bIsChangedColor)
	{
		CurrentColor = FMath::Lerp(CurrentColor, TargetColor, DeltaSeconds * ChangedColorVelocity);
		PaintingMatInst->SetVectorParameterValue("OverlayColor", CurrentColor);
		
		CurrentIntensity = FMath::Lerp(CurrentIntensity, TargetIntensity, DeltaSeconds * ChangedColorVelocity);
		PaintingMatInst->SetScalarParameterValue("Intensity", CurrentIntensity);

		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Purple,
FString::Printf(TEXT("%f %f %f %f"),CurrentColor.R, CurrentColor.G, CurrentColor.B, CurrentColor.A
));

		if(FMath::Abs(CurrentIntensity - TargetIntensity) <= 0.01f)
			bIsChangedColor = false;
	}
}

void ACollectObject::SetPaintedColorAndIntensity(FLinearColor brushColor)
{
	if(bIsPaintComplete)
		return;

	/*if(!IsExistInVaildPaintArray(brushColor))
		return;*/
	
	++PaintedCount;
	
	bIsChangedColor = true;

	CurrentColor = GetPaintedColor();
	TargetColor = FLinearColor(
		FMath::Lerp(CurrentColor.R, brushColor.R, 0.5f),
		FMath::Lerp(CurrentColor.G, brushColor.G, 0.5f),
		FMath::Lerp(CurrentColor.B, brushColor.B, 0.5f),
		1.0f);

	// Emissive
	PaintingMatInst->GetScalarParameterValue(FName(TEXT("Intensity")), CurrentIntensity);
	TargetIntensity = FMath::Lerp(CurrentIntensity, 1.0f, 0.5f);
}

void ACollectObject::SetBaseTexture(UTexture2D* texture)
{
	if(bIsPaintComplete)
		return;
	
	PaintingMatInst->SetTextureParameterValue("BaseTexture", texture);
}

FLinearColor ACollectObject::GetPaintedColor()
{
	FLinearColor currentColor;
	PaintingMatInst->GetVectorParameterValue(FName(TEXT("OverlayColor")), currentColor);
	return currentColor;
}

void ACollectObject::SetPaintedColor(FLinearColor color)
{
	if(!bIsPaintComplete)
		return;
	
	PaintingMatInst->SetVectorParameterValue("OverlayColor", color);
}

void ACollectObject::SetPaintedComplete()
{
	bIsPaintComplete = true;
	PaintingMatInst->SetVectorParameterValue("OverlayColor", OriginColor);
}

bool ACollectObject::IsExistInVaildPaintArray(FLinearColor findColor)
{
	for(auto& color : VaildPaintColors)
	{
		if(color == findColor)
			return true;
	}

	return false;
}
