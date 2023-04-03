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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UDataTable* ItemDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	FItem ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* ActiveTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Painted Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* InActiveTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* ChildActiveTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collect Object",meta=(AllowPrivateAccess))
	UTexture2D* ChildInActiveTexture;

public:
	APaintedCollectObject();

	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object", meta=(AllowPrivateAccess))
	int ItemID = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsColorActive = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsDrawing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object", meta=(AllowPrivateAccess))
	ECollectType CollectType;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Painted Collect Object")
	int PaintedCount = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Painted Collect Object")
	int NeedsPaintedCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object")
	float SpawnDelayTime = 3.0f;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PaintToObject(FLinearColor PaintedColor);

	UFUNCTION(BlueprintCallable)
	void SetActiveCollectObject(bool active, int index);

	UFUNCTION(BlueprintCallable)
	void SetChildCollectObjectTexture(UTexture2D* texture);
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FTimerHandle> SpawnTimerHandles;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting")
	TArray<ACollectObject*> CollectObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInterface* BrushMatTemplate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInterface* PaintingMatTemplate;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Painted Collect Object | Setting") 
	UMaterialInstanceDynamic* BrushMatInst;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UMaterialInstanceDynamic* PaintingMatInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetTemplate;
	
	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetPallet;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetCopy;
};