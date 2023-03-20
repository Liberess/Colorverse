#pragma once

#include "CoreMinimal.h"
#include "InteractObject.h"
#include "InteractWidget.h"
#include "InventoryManager.h"
#include "LivingEntity.h"
#include "CombatSystem.h"
#include "ColorverseCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "ColorverseCharacter.generated.h"

UCLASS(config=Game)
class AColorverseCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat System", meta = (AllowPrivateAccess = "true"))
	class UCombatSystem* CombatSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Living Entity", meta = (AllowPrivateAccess = "true"))
	class ULivingEntity* LivingEntity;
	
public:
	AColorverseCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player Movement")
	bool bIsRunning;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float WalkSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float AutoRunStartDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float RollSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float RollDelay;
	
	UFUNCTION(BlueprintCallable)
	void SetEnabledToggleRun();

	virtual void Jump() override;
	virtual void StopJumping() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetDisabledAttack(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Roll();

	UFUNCTION(BlueprintCallable)
	void SetDisabledRoll();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category=Interact)
	bool bIsInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Interact)
	AInteractObject* InteractObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interact)
	TSubclassOf<UUserWidget> InteractWidgetClass;
	
	UPROPERTY()
	UInteractWidget* InteractWidget;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ControlInventory();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ControlMaker();

private:
	bool bIsRunTimer;
	FTimerHandle ToggleRunTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Living Entity")
	bool bIsDamageable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Combat System")
	bool bIsRolling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category="Combat System")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Combat System")
	bool bIsAttacked;
	
	FTimerHandle RollTimer;

	bool bIsWatchingInteractWidget;

	UInventoryManager* InvenMgr;

	UPROPERTY()
	class UColorverseCharacterAnimInstance* ColorverseAnim;

protected:
	void OnResetVR();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class UCombatSystem* GetCombatSystem() const { return CombatSystem; }
	FORCEINLINE class ULivingEntity* GetLivingEntity() const { return LivingEntity; }
};