#include "ColorverseCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Statue.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#define Print(duration, text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1,duration, FColor::Blue, text);

AColorverseCharacter::AColorverseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AColorverseCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AColorverseCharacter::OnOverlapEnd);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CombatSystem = CreateDefaultSubobject<UCombatSystem>(TEXT("CombatSystem"));
	LivingEntity = CreateDefaultSubobject<ULivingEntity>(TEXT("LivingEntity"));

	BrushColors = {
		FLinearColor::FromSRGBColor(FColor::Red),
		FLinearColor::FromSRGBColor(FColor::Yellow),
		FLinearColor::FromSRGBColor(FColor::Blue)
	};
	
	/*BrushColors.Add(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
	BrushColors.Add(FLinearColor(1.0f, 1.0f, 0.0f, 1.0f));
	BrushColors.Add(FLinearColor(0.0f, 0.0f, 1.0f, 1.0f));*/
}

void AColorverseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetCharacterMovement()))
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

	InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();

	bIsDamageable = true;
}

void AColorverseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AColorverseCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AColorverseCharacter::StopJumping);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AColorverseCharacter::Attack);
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AColorverseCharacter::Roll);

	PlayerInputComponent->BindAxis("MoveForward", this, &AColorverseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AColorverseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AColorverseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AColorverseCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AColorverseCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AColorverseCharacter::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AColorverseCharacter::OnResetVR);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AColorverseCharacter::Interact);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AColorverseCharacter::ControlInventory);

	PlayerInputComponent->BindAction<TDelegate<void(ECombineColors)>>(
		TEXT("RedPaint"), IE_Pressed, this, &AColorverseCharacter::ChangeEquipPaint, ECombineColors::Red);
	PlayerInputComponent->BindAction<TDelegate<void(ECombineColors)>>(
		TEXT("YellowPaint"), IE_Pressed, this, &AColorverseCharacter::ChangeEquipPaint, ECombineColors::Yellow);
	PlayerInputComponent->BindAction<TDelegate<void(ECombineColors)>>(
		TEXT("BluePaint"), IE_Pressed, this, &AColorverseCharacter::ChangeEquipPaint, ECombineColors::Blue);
	PlayerInputComponent->BindAction<TDelegate<void(ECombineColors)>>(
		TEXT("EmptyPaint"), IE_Pressed, this, &AColorverseCharacter::ChangeEquipPaint, ECombineColors::Empty);
}

void AColorverseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ColorverseAnim = Cast<UColorverseCharacterAnimInstance>(GetMesh()->GetAnimInstance());

	if (!IsValid(ColorverseAnim))
		return;

	ColorverseAnim->OnNextAttackCheck.AddDynamic(this, &AColorverseCharacter::SetNextAttackCheck);
	ColorverseAnim->OnStartAttackJudg.AddDynamic(this, &AColorverseCharacter::SetEnableCanAttackTrace);
	ColorverseAnim->OnEndAttackJudg.AddDynamic(this, &AColorverseCharacter::SetDisableCanAttackTrace);
	ColorverseAnim->OnEndAttack.AddDynamic(this, &AColorverseCharacter::SetDisabledAttack);
}

void AColorverseCharacter::SetNextAttackCheck()	
{
	CombatSystem->bCanNextCombo = false;

	if (CombatSystem->bIsComboInputOn)
	{
		CombatSystem->AttackStartComboState();
		ColorverseAnim->JumpToAttackMontageSection(CombatSystem->CurrentCombo);
	}
}

void AColorverseCharacter::SetEnableCanAttackTrace()
{
	CombatSystem->bIsCanAttackTrace = true;
	AttackHitResults.Empty();

	IsDrawing = true;
}

void AColorverseCharacter::SetDisableCanAttackTrace()
{
	CombatSystem->bIsCanAttackTrace = false;

	IsDrawing = false;
	
	if(IsValid(CurrentPaintedCollectObj))
		CurrentPaintedCollectObj->IsDrawing = false;
}

#pragma region Movement 
void AColorverseCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AColorverseCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AColorverseCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AColorverseCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AColorverseCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AColorverseCharacter::MoveForward(float Value)
{
	if (LivingEntity->GetDead())
		return;

	if (bIsAttacked)
		return;

	if ((Controller != nullptr))
	{
		if (Value != 0.0f)
		{
			if (bIsAttacking)
			{
				Value *= 0.0001;
			}

			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AColorverseCharacter::MoveRight(float Value)
{
	if (LivingEntity->GetDead())
		return;

	if (bIsAttacked)
		return;

	if ((Controller != nullptr))
	{
		if (Value != 0.0f)
		{
			if (bIsAttacking)
			{
				Value *= 0.0001;
			}

			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
}

void AColorverseCharacter::SetEnabledToggleRun()
{
	bIsRunning = true;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AColorverseCharacter::Jump()
{
	if (LivingEntity->GetDead())
		return;

	if (bIsAttacking || bIsAttacked)
		return;

	Super::Jump();
}

void AColorverseCharacter::StopJumping()
{
	if (bIsAttacking || bIsAttacked)
		return;

	Super::StopJumping();
}
#pragma endregion Movement

void AColorverseCharacter::Attack_Implementation()
{
	if (LivingEntity->GetDead())
		return;

	if (bIsAttacked)
		return;

	if (bIsRolling)
		return;

	if (GetCharacterMovement()->IsFalling())
		return;

	if (bIsAttacking == true)
	{
		if (CombatSystem->bCanNextCombo)
		{
			CombatSystem->bIsComboInputOn = true;
		}
	}
	else
	{
		CombatSystem->AttackStartComboState();
		ColorverseAnim->PlayAttackMontage();
		bIsAttacking = true;
	}
}

void AColorverseCharacter::SetDisabledAttack_Implementation()
{
	bIsAttacking = false;
	CombatSystem->AttackEndComboState();
}

void AColorverseCharacter::Roll_Implementation()
{
	if (LivingEntity->GetDead())
		return;

	if (bIsAttacked || bIsAttacking)
		return;

	if (!bIsRunning || bIsRolling)
		return;

	if (GetCharacterMovement()->IsFalling())
		return;

	bIsRolling = true;
	bIsDamageable = false;

	Print(1.0f, TEXT("Roll On"));

	GetWorldTimerManager().ClearTimer(RollTimer);
	GetWorldTimerManager().SetTimer(RollTimer, this, &AColorverseCharacter::SetDisabledRoll, RollDelay, true);
}

void AColorverseCharacter::SetDisabledRoll_Implementation()
{
	bIsRolling = false;
	bIsDamageable = true;
	Print(1.0f, TEXT("Roll Off"));
}

void AColorverseCharacter::HitCheck_Implementation()
{

}

void AColorverseCharacter::Attacked_Implementation(FDamageMessage damageMessage)
{
	if (LivingEntity->GetDead())
		return;

	LivingEntity->ApplyDamage(damageMessage);

	if (LivingEntity->CurrentHealth <= 0)
	{
		Dead();
		return;
	}

	bIsAttacked = true;
	ColorverseAnim->PlayDamagedMontage();
}

void AColorverseCharacter::Dead_Implementation()
{
	LivingEntity->SetDead(true);
}

void AColorverseCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                          class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		InteractObject = Cast<AInteractObject>(OtherActor);
		if (IsValid(InteractObject))
		{
			bIsInteract = true;
			
			if (!bIsWatchingInteractWidget && InteractObject->GetInteractable())
			{
				if (IsValid(InteractWidgetClass))
				{
					InteractWidget = Cast<UInteractWidget>(CreateWidget(GetWorld(), InteractWidgetClass));
					if (InteractWidget != nullptr)
					{
						InteractWidget->SetInteractText(FText::FromString(InteractObject->InteractWidgetDisplayTxt));
						bIsWatchingInteractWidget = true;
						InteractWidget->AddToViewport();
					}
				}
			}
		}
	}
}

void AColorverseCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if (IsValid(InteractObject) && InteractObject == OtherActor)
		{
			InteractObject = nullptr;
			bIsInteract = false;

			if (InteractWidget != nullptr)
			{
				bIsWatchingInteractWidget = false;
				InteractWidget->RemoveFromParent();
				InteractWidget = nullptr;
			}
		}
	}
}

void AColorverseCharacter::ChangeEquipPaint_Implementation(ECombineColors CombineColor)
{
	CombatSystem->CurrentPaintColor = CombineColor;

	if(CombineColor != ECombineColors::Empty)
	{
		CombatSystem->SetColorBuff();
		CombatSystem->SetElementBuff((int)CombineColor);
	}
}

void AColorverseCharacter::ControlInventory_Implementation()
{
	InvenMgr->SetInventoryUI(true, true);
}

void AColorverseCharacter::Interact_Implementation()
{
	if (!bIsInteract || !IsValid(InteractObject))
		return;

	InteractObject->OnInteract();
	
	if (bIsWatchingInteractWidget && InteractWidget != nullptr)
	{
		bIsWatchingInteractWidget = false;
		InteractWidget->RemoveFromParent();
		InteractWidget = nullptr;
	}
}
