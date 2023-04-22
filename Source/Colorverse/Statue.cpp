#include "Statue.h"

AStatue::AStatue()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();
	StatueIndex = static_cast<int>(StatueColor);
}

void AStatue::OnEnter()
{

}

void AStatue::OnInteract()
{
	Super::OnInteract();
}

void AStatue::OnExit()
{
	//Super::OnExit();
}
