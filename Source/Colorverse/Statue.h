#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Statue.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AStatue : public AInteractObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AStatue();
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnEnter() override;
	virtual void OnInteract() override;
	virtual void OnExit() override;

	UPROPERTY()
	bool bIsRecoveryComplete = false;

	UPROPERTY()
	bool bIsChangedColor = false;

	UPROPERTY()
	bool bIsWorldMineColorRecoveryComplete = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int StatueIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	ECombineColors StatueColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FLinearColor CurrentColor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FLinearColor TargetColor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FLinearColor CompleteColor;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UMaterialInstanceDynamic* PaintingMatInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float ChangedColorVelocity = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int RecoveryCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int MaxRecoveryCount = 3;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActiveUnlockEffect();
	
	UFUNCTION(BlueprintCallable)
	void IncreaseColor();

	UFUNCTION(BlueprintCallable)
	void DecreaseColor();
};
