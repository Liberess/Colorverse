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

public:
	APaintedCollectObject();

	virtual void BeginPlay() override;
	
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
	void PaintToObject();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SpawnCollectObject();
	
	UFUNCTION(BlueprintCallable)
	void SpawnCollectObjectByIndex(int ObjectIndex);

	UPROPERTY(BlueprintReadOnly)
	TArray<FTimerHandle> SpawnTimerHandles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object")
	TArray<ACollectObject*> CollectObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object") 
	UMaterialInstanceDynamic* BrushMatInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object")
	UMaterialInstanceDynamic* PaintingMatInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTarget;
	
	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetPallet;

	UPROPERTY(BlueprintReadWrite, Category="Painted Collect Object | Setting")
	UTextureRenderTarget2D* PaintingRenderTargetCopy;
};