// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledObject.h"

// Sets default values
APooledObject::APooledObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	if (collision != nullptr)
	{
		RootComponent = collision;
		collision->SetCollisionProfileName("PooledObject");
	}

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (mesh != nullptr)
	{
		mesh->SetupAttachment(RootComponent);
		mesh->SetCollisionProfileName("PooledObject");
	}

	SetActive(true);
}

// Called when the game starts or when spawned
void APooledObject::BeginPlay()
{
	Super::BeginPlay();
	
	SetActive(true);
}

// Called every frame
void APooledObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledObject::SetActive(bool InActive)
{
	active = InActive;
	collision->SetSimulatePhysics(InActive);
	SetActorHiddenInGame(!InActive);
	SetActorEnableCollision(InActive);
	SetActorTickEnabled(InActive);
}

void APooledObject::Deactivate()
{
	Init();
	SetActive(false);
}

void APooledObject::Init()
{
	IsInteractable = true;
	SetActorLocation(FVector().ZeroVector);
	SetActorRotation(FRotator().ZeroRotator);
}

void APooledObject::CreatePooledObject_Implementation()
{
	IsInteractable = true;

	SetActive(true);
}

void APooledObject::DistroyPooledObject_Implementation()
{
	IsInteractable = false;

	Deactivate();
}