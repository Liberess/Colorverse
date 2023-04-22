#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "InteractObject.h"
#include "Statue.generated.h"

UCLASS(Blueprintable)
class COLORVERSE_API AStatue : public AInteractObject
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AStatue();
	virtual void OnEnter() override;
	virtual void OnInteract() override;
	virtual void OnExit() override;

	// 성소가 해금됐는지, 안 됐는지
	UPROPERTY()
	bool bIsUnlockComplete = false;
	
	UPROPERTY()
	bool bIsRecoveryComplete = false;

	UPROPERTY()
	bool bIsWorldMineColorRecoveryComplete = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int StatueIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	ECombineColors StatueColor;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ActiveUnlockEffect();
};
