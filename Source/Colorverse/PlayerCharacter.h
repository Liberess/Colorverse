#pragma once

#include "CoreMinimal.h"
#include "ColorverseCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class COLORVERSE_API APlayerCharacter : public AColorverseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player Movement")
	void Roll();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Movement")
	float RollSpeed;
};
