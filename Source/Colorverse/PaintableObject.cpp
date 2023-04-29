#include "PaintableObject.h"
#include "ColorverseCharacter.h"
#include "Kismet/GameplayStatics.h"

APaintableObject::APaintableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(DefaultRoot);
	
	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCol->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	BoxCol->SetCollisionProfileName(TEXT("Trigger"));
	BoxCol->SetupAttachment(DefaultRoot);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(DefaultRoot);
}

void APaintableObject::BeginPlay()
{
	Super::BeginPlay();

	PaintingMatInst = UMaterialInstanceDynamic::Create(PaintingMatTemplate, this);
	StaticMesh->SetMaterial(0, PaintingMatInst);
}

void APaintableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsPaintedComplete && bIsColorChanged)
	{
		CurrentColor = FMath::Lerp(CurrentColor, TargetColor, DeltaTime * 2.0f);
		PaintingMatInst->SetVectorParameterValue("OverlayColor", CurrentColor);

		if(FLinearColor::Dist(CurrentColor, TargetColor) <= 0.01f)
		{
			bIsColorChanged = false;

			if(PaintedCount >= PaintedCapacity)
			{
				CurrentColor = TargetColor;
				PaintingMatInst->SetVectorParameterValue("OverlayColor", CurrentColor);

				if(bIsRightColor)
				{
					bIsPaintedComplete = true;
					CompletePainted();
				}
			}
		}
	}
}

void APaintableObject::PaintToObject_Implementation(FLinearColor PaintColor, ECombineColors CurrentColorTag)
{
	bIsRightColor = (CurrentColorTag == ColorTag) ? true : false;
	bIsColorChanged = true;
	
	if(CurrentColorTag != ECombineColors::Empty)
	{
		if(!bIsPaintedComplete)
		{
			++PaintedCount;
			PaintingMatInst->GetVectorParameterValue(FName(TEXT("OverlayColor")), CurrentColor);

			if(PaintedCount >= PaintedCapacity)
			{
				TargetColor = PaintColor;
			}
			else
			{
				TargetColor = FLinearColor(
				FMath::Lerp(CurrentColor.R, PaintColor.R, 0.5f),
				FMath::Lerp(CurrentColor.G, PaintColor.G, 0.5f),
				FMath::Lerp(CurrentColor.B, PaintColor.B, 0.5f),
				1.0f);
			}
		}
	}
	else
	{
		TargetColor = FLinearColor(FColor::White);
		PaintedCount = 0;
		bIsPaintedComplete = false;
	}
}

