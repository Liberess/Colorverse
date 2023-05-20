#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Sanctum.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API ASanctum : public AInteractObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ASanctum();
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnEnter_Implementation() override;
	virtual void OnInteract_Implementation() override;
	virtual void OnExit_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsRecoveryComplete = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsChangedColor = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsUnlock = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int StanctumID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	EPuzzleTag PuzzleTag = EPuzzleTag::Puzzle_Red;
	
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
