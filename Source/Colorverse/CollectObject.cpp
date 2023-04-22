#include "CollectObject.h"
#include "InventoryManager.h"
#include "PaintedCollectObject.h"

ACollectObject::ACollectObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/DataTables/DT_ItemData"));
	if (DataTable.Succeeded())
		ItemDT = DataTable.Object;
}

void ACollectObject::BeginPlay()
{
	Super::BeginPlay();

	IsInteractable = false;
	CurrentScale = FVector::ZeroVector;
}

void ACollectObject::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!bIsPaintComplete && bIsChangedColor && !bIsSeparated)
	{
		CurrentColor = FMath::Lerp(CurrentColor, TargetColor, DeltaSeconds * ChangedColorVelocity);
		PaintingMatInst->SetVectorParameterValue("OverlayColor", CurrentColor);
		
		CurrentIntensity = FMath::Lerp(CurrentIntensity, TargetIntensity, DeltaSeconds * ChangedColorVelocity);
		PaintingMatInst->SetScalarParameterValue("Intensity", CurrentIntensity);

		if(FMath::Abs(CurrentIntensity - TargetIntensity) <= 0.01f)
		{
			bIsChangedColor = false;
			
			if(PaintedCount >= NeedsPaintedCount)
				bIsPaintComplete = true;
		}
	}

	if(bIsGrown)
	{
		CurrentScale = FMath::Lerp(CurrentScale, TargetScale, DeltaSeconds / 2.0f);
		StaticMesh->SetRelativeScale3D(CurrentScale);

		GEngine->AddOnScreenDebugMessage(10, 1.0f, FColor::Green,
			FString::Printf(TEXT("%f"), CurrentScale.X));
		
		if(FMath::Abs(TargetScale.X - CurrentScale.X) <= 0.01f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TEXT("gg"));
			bIsGrown = false;
			StaticMesh->SetRelativeScale3D(TargetScale);
		}
	}
}

void ACollectObject::Interact_Implementation()
{
	//Super::Interact_Implementation();

	if(!bIsSeparated)
		return;

	UInventoryManager* InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	InvenMgr->AddInventoryItem(ItemData);
}

void ACollectObject::SetPaintedColorAndIntensity(ECombineColors colorTag, FLinearColor brushColor)
{
	if(bIsPaintComplete)
		return;

	if(PaintedCount < 0 || PaintedCount >= PaintComboData.ComboColors.Num())
		return;

	if(PaintComboData.ComboColors[PaintedCount] != colorTag)
		return;

	++PaintedCount;
	bIsChangedColor = true;

	CurrentColor = GetPaintedColor();

	if(PaintedCount >= NeedsPaintedCount)
	{
		TargetColor = FLinearColor(
			PaintComboData.ResultColor.R,
			PaintComboData.ResultColor.G,
			PaintComboData.ResultColor.B,
		1.0f);

		BoxCol->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		APaintedCollectObject* paintObj = Cast<APaintedCollectObject>(GetParentActor());
		paintObj->SetRecoveryColorComplete(ECombineColors::Red);
	}
	else
	{
		TargetColor = FLinearColor(
		FMath::Lerp(CurrentColor.R, brushColor.R, 0.5f),
		FMath::Lerp(CurrentColor.G, brushColor.G, 0.5f),
		FMath::Lerp(CurrentColor.B, brushColor.B, 0.5f),
		1.0f);
	}
	
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

void ACollectObject::SetCollectObjectData(FName _itemName)
{
	ItemData = *(ItemDT->FindRow<FItem>(_itemName, ""));
	InteractWidgetDisplayTxt = ItemData.Name.ToString();
}
