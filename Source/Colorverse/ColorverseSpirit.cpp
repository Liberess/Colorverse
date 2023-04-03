// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorverseSpirit.h"

// Sets default values
AColorverseSpirit::AColorverseSpirit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectPooler = CreateDefaultSubobject<UMyObjectPool>(TEXT("ObjectPooler"));
}

// Called when the game starts or when spawned
void AColorverseSpirit::BeginPlay()
{
	Super::BeginPlay();
	
	SetActive(true);
}

// Called every frame
void AColorverseSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorverseSpirit::SetActive(bool value)
{
	active = value;
	SetActorHiddenInGame(!value);
	SetActorEnableCollision(value);
	SetActorTickEnabled(value);
}

void AColorverseSpirit::Attack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Bullet");
	SpawnBullet();
}

void AColorverseSpirit::SpawnBullet()
{
	APooledObject* PoolableActor = ObjectPooler->GetPooledObject();
	if (PoolableActor == nullptr)
	{
		return;
	}

	FVector newPos = GetActorLocation();
	PoolableActor->SetActorLocation(newPos);
	FRotator newRot = GetActorRotation();
	PoolableActor->SetActorRotation(newRot);

	PoolableActor->CreatePooledObject();
}