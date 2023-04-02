// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyObjectPool.h"
#include "ColorverseSpirit.generated.h"

UCLASS()
class COLORVERSE_API AColorverseSpirit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AColorverseSpirit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Spawner")
	UMyObjectPool* ObjectPooler;

private:
	bool active;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void SetActive(bool value);

	FORCEINLINE class UMyObjectPool* GetObjectPooler() { return ObjectPooler; }

private:
	void SpawnBullet();
};
