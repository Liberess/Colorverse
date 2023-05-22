// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColorverseMonster.h"
#include "Enums.h"
#include "ColorverseMonster_middle.generated.h"

/**
 * 
 */
UCLASS()
class COLORVERSE_API AColorverseMonster_middle : public AColorverseMonster
{
	GENERATED_BODY()
	
public:
	AColorverseMonster_middle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat System")
	EPuzzleTag PuzzleTag;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
