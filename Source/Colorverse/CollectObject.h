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

protected:
	virtual void BeginPlay() override;

public:
	ACollectObject();

	UFUNCTION(BlueprintCallable)
	void SetColorIntensity(int amount);

	UFUNCTION(BlueprintCallable)
	void SetBaseTexture(UTexture2D* texture);
	
	UFUNCTION(BlueprintCallable)
	FLinearColor GetPaintedColor();
};
