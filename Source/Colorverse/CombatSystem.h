// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	void AttackStartComboState();
	void AttackEndComboState();

	
};
