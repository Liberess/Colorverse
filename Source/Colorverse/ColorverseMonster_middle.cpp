// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorverseMonster_middle.h"

AColorverseMonster_middle::AColorverseMonster_middle()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AColorverseMonster_middle::BeginPlay()
{
	Super::BeginPlay();
}

void AColorverseMonster_middle::RunAI_Implementation()
{

}

// Called every frame
void AColorverseMonster_middle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}