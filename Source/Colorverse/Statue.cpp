#include "Statue.h"
#include "ColorverseCharacter.h"
#include "CombatSystem.h"
#include "Kismet/GameplayStatics.h"

AStatue::AStatue()
{
	//PrimaryComponentTick.bCanEverTick = true;
}

void AStatue::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsChangedColor)
	{
		CurrentColor = FMath::Lerp(CurrentColor, TargetColor, DeltaSeconds * ChangedColorVelocity);
		PaintingMatInst->SetVectorParameterValue("EmissiveColor", CurrentColor);

		if (FMath::Abs(CurrentColor.R - TargetColor.R) <= 0.01f)
		{
			bIsChangedColor = false;

			if(bIsRecoveryComplete)
			{
				
			}
		}
	}
}

void AStatue::BeginPlay()
{
	Super::BeginPlay();

	StatueIndex = static_cast<int>(StatueColor);
	
	AColorverseCharacter* Character = Cast<AColorverseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CompleteColor = Character->GetCombatSystem()->GetCurrentPaintLinearColorByEnum(StatueColor);
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

void AStatue::IncreaseColor()
{
	bIsChangedColor = true;
	
	++RecoveryCount;
	
	PaintingMatInst->GetVectorParameterValue(FName(TEXT("EmissiveColor")), CurrentColor);
	
	if (RecoveryCount >= MaxRecoveryCount)
	{
		bIsRecoveryComplete = true;
		TargetColor = CompleteColor;
	}
	else
	{
		TargetColor = FLinearColor(
			FMath::Lerp(CurrentColor.R, CompleteColor.R, 0.2f),
			FMath::Lerp(CurrentColor.G, CompleteColor.G, 0.2f),
			FMath::Lerp(CurrentColor.B, CompleteColor.B, 0.2f),
			1.0f);
	}
}

void AStatue::DecreaseColor()
{
	bIsChangedColor = true;
	
	--RecoveryCount;
	
	PaintingMatInst->GetVectorParameterValue(FName(TEXT("EmissiveColor")), CurrentColor);
	
	if (RecoveryCount <= 0)
	{
		TargetColor = FLinearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		TargetColor = FLinearColor(
			FMath::Lerp(CurrentColor.R, 0.0f, 0.5f),
			FMath::Lerp(CurrentColor.G, 0.0f, 0.5f),
			FMath::Lerp(CurrentColor.B, 0.0f, 0.5f),
			1.0f);
	}
}
