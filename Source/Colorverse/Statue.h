#pragma once

#include "CoreMinimal.h"
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
	bool bIsUnlock = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	int StatueIndex = 0;

	// 성소와 상호작용하며 인벤토리 UI가 열렸는지
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsOpenInventoryByStatue = false;

	// 성소를 해금하기 위해 제물을 바친 정도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int UnlockCount = 0;

	// 성소를 해금하기 위한 목표치 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int UnlockCapacity = 3;

	// 성소가 있는 지역의 색을 되찾은 정도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float RecoveryAmount = 0.0f;

	// 성소가 있는 지역의 색을 되찾기 위해 채워야 하는 목표치
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RecoveryCapacity = 100.0f;
};
