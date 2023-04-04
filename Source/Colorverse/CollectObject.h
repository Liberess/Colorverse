#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "IItem.h"
#include "InteractObject.h"
#include "CollectObject.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API ACollectObject : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	USceneComponent* DefaultRoot = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FItem ItemData;

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
	
	UPROPERTY(BlueprintReadWrite, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor OriginColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor CurrentColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor TargetColor;

	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor PreviousPaintColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	FLinearColor NextPaintColor;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float CurrentIntensity = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float TargetIntensity = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))
	float ChangedColorVelocity = 2.0f;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	ACollectObject();

	UPROPERTY(BlueprintReadOnly, Category="Collect Object | Setting", meta=(AllowPrivateAccess))\
	bool bIsPaintComplete = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Collect Object | Setting")
	int PaintedCount = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Collect Object | Setting")
	int NeedsPaintedCount = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collect Object | Setting")
	TArray<FLinearColor> VaildPaintColors;

	UFUNCTION(BlueprintCallable)
	void SetPaintedColorAndIntensity(FLinearColor color);

	UFUNCTION(BlueprintCallable)
	void SetBaseTexture(UTexture2D* texture);
	
	UFUNCTION(BlueprintCallable)
	FLinearColor GetPaintedColor();

	UFUNCTION(BlueprintCallable)
	void SetPaintedColor(FLinearColor color);

	UFUNCTION(BlueprintCallable)
	void SetPaintedComplete();

	UFUNCTION(BlueprintCallable)
	bool IsExistInVaildPaintArray(FLinearColor findColor);
};
