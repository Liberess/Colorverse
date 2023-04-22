// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManager.h"
#include "CombatSystem.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COLORVERSE_API UCombatSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	// 플레이어 능력치
	UPROPERTY(Category = "Character Status (General Settings)", EditAnywhere, BlueprintReadWrite)
	float ATK;

	UPROPERTY(Category = "Character Status (General Settings)", EditAnywhere, BlueprintReadWrite)
	float DEF;

	UPROPERTY(Category = "Character Status (General Settings)", EditAnywhere, BlueprintReadWrite)
	float EXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Status (General Settings)")
	ECombineColors CurrentPaintColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Status (General Settings)")
	TArray<FLinearColor> PaintColorTemplates;

	// 물감 있을 때 속성 버프
	UPROPERTY(Category = "Character Status (General Settings)", EditAnywhere, BlueprintReadWrite)
	float ColorBuff;

	// 상성 가위바위보 강화 속성 버프
	UPROPERTY(Category = "Character Status (General Settings)", EditAnywhere, BlueprintReadWrite)
	float ElementBuff;

	UPROPERTY(Category = "Character Buff", EditAnywhere, BlueprintReadWrite)
	bool bIsOnColor;

	UPROPERTY(Category = "Character Buff", EditAnywhere, BlueprintReadWrite)
	TArray<bool> bIsOnElements;

	// 콤보 관련
	UPROPERTY(Category = "Character Combo", EditAnywhere, BlueprintReadWrite)
	int32 MaxCombo;

	UPROPERTY(Category = "Character Combo", EditAnywhere, BlueprintReadWrite)
	int32 CurrentCombo;

	UPROPERTY(Category = "Character Combo", EditAnywhere, BlueprintReadWrite)
	bool bCanNextCombo;

	UPROPERTY(Category = "Character Combo", EditAnywhere, BlueprintReadWrite)
	bool bIsComboInputOn;

	UPROPERTY(Category = "Character Attack", EditAnywhere, BlueprintReadWrite)
	bool bIsCanAttackTrace;

public:
	UFUNCTION(BlueprintCallable)
	void SetColorBuff();

	UFUNCTION(BlueprintCallable)
	void SetElementBuff(int color);

	UFUNCTION(BlueprintCallable)
	float GetCurrentATK();

	UFUNCTION(BlueprintCallable)
	FLinearColor GetCurrentPaintLinearColor()
	{
		return PaintColorTemplates[static_cast<int>(CurrentPaintColor)];
	}

	UFUNCTION(BlueprintCallable)
	FLinearColor GetCurrentPaintLinearColorByEnum(ECombineColors EColor)
	{
		return PaintColorTemplates[static_cast<int>(EColor)];
	}

	UFUNCTION(BlueprintCallable)
	float GetCurrentPaintColorAmount();

	UFUNCTION(BlueprintCallable)
	void SetCurrentPaintColorAmount(float value);

	void AttackStartComboState();
	void AttackEndComboState();
};
