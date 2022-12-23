#pragma once

#include "CoreMinimal.h"
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

private:
	bool bIsRunTimer;
	FTimerHandle ToggleRunTimer;

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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Roll();

	UFUNCTION(BlueprintCallable)
	void SetDisabledRoll();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="LivingEntity")
	bool bIsDamageable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess), Category="Player Movement")
	bool bIsRolling;
	
	FTimerHandle RollTimer;

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

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
