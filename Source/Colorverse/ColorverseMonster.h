// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorverseCharacter.h"
#include "ColorverseMonster.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API AColorverseMonster : public AColorverseCharacter
{
	GENERATED_BODY()
	
public:
	AColorverseMonster();

protected:
	bool active;

public:
	UFUNCTION(BlueprintCallable)
	void SetActive(bool value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
