#pragma once

#include "CoreMinimal.h"
#include "CollectObject.h"
#include "Enums.h"
#include "IItem.h"
#include "InteractObject.h"
#include "PaintedCollectObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API APaintedCollectObject : public AInteractObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UDataTable* ItemDT;

	UPROPERTY(BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UDataTable* PaintComboDT;

	UPROPERTY(BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	FPaintCombo PaintComboData;

	UPROPERTY(BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	FItem ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* ActiveTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* InActiveTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object | Child",meta=(AllowPrivateAccess))
	UTexture2D* ChildActiveTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object | Child",meta=(AllowPrivateAccess))
	UTexture2D* ChildInActiveTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object | Child",meta=(AllowPrivateAccess))
	FLinearColor GroupActiveColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object | Child",meta=(AllowPrivateAccess))
	FLinearColor GroupInActiveColor;

public:
	APaintedCollectObject();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Child", meta=(AllowPrivateAccess))
	int ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Child", meta=(AllowPrivateAccess))
	EPaintComboColors PaintComboColorTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsColorActive = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsDrawing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object", meta=(AllowPrivateAccess))
	ECollectType CollectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Child")
	float SpawnDelayTime = 3.0f;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PaintToObject(ECombineColors colorTag, FLinearColor PaintedColor);

	UFUNCTION(BlueprintCallable)
	void SetActiveCollectObject(bool active, int index);

	UFUNCTION(BlueprintCallable)
	void SetChildCollectObjectTexture(UTexture2D* texture);
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FTimerHandle> SpawnTimerHandles;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Child")
	TArray<ACollectObject*> CollectObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInterface* BrushMatTemplate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInterface* PaintingMatTemplate;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInstanceDynamic* BrushMatInst;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UMaterialInstanceDynamic* PaintingMatInst;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Child")
	UMaterialInstanceDynamic* GroupMatInst;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetTemplate;
	
	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetPallet;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetCopy;
};