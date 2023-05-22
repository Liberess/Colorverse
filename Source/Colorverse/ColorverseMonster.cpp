// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorverseMonster.h"

AColorverseMonster::AColorverseMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AColorverseMonster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AColorverseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorverseMonster::Destroy_Implementation()
{

}

void AColorverseMonster::SetActive(bool value)
{
	active = value;
	SetActorHiddenInGame(!value);
	SetActorTickEnabled(value);
}