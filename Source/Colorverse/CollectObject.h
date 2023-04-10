#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "IItem.h"
#include "InteractObject.h"
#include "CollectObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API ACollectObject : public AInteractObject
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category="Collect Object",meta=(AllowPrivateAccess))
	UDataTable* ItemDT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess)) 
	UMaterialInterface* BrushMatTemplate;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess)) 
	UMaterialInterface* PaintingMatTemplate;

	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess)) 
	UMaterialInstanceDynamic* BrushMatInst;

	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	UMaterialInstanceDynamic* PaintingMatInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	UTextureRenderTarget2D* PaintingRenderTargetTemplate;
	
	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	UTextureRenderTarget2D* PaintingRenderTargetPallet;

	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	UTextureRenderTarget2D* PaintingRenderTargetCopy;

	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	bool bIsChangedColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor CurrentColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor TargetColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float CurrentIntensity = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float TargetIntensity = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float ChangedColorVelocity = 2.0f;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Interact_Implementation() override;

public:
	ACollectObject();

	UPROPERTY(BlueprintReadWrite, Category="Collect Object")
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FItem ItemData;

	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting")
	FPaintCombo PaintComboData;

	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting")
	bool bIsPaintComplete = false;

	// Parent에게 상속된 Collect Object인지 아닌지
	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting")
	bool bIsSeparated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Collect Object | Setting")
	int PaintedCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object | Setting")
	int NeedsPaintedCount = 3;

	UFUNCTION(BlueprintCallable)
	void SetPaintedColorAndIntensity(ECombineColors colorTag, FLinearColor color);

	UFUNCTION(BlueprintCallable)
	void SetBaseTexture(UTexture2D* texture);
	
	UFUNCTION(BlueprintCallable)
	FLinearColor GetPaintedColor();

	UFUNCTION(BlueprintCallable)
	void SetPaintedColor(FLinearColor color);

	UFUNCTION(BlueprintCallable)
	void SetCollectObjectData(FName _itemName);

	UPROPERTY(BlueprintReadWrite)
	bool bIsGrown = false;
	
	UPROPERTY(BlueprintReadWrite)
	FVector CurrentScale;

	UPROPERTY(BlueprintReadWrite)
	FVector TargetScale;
};
