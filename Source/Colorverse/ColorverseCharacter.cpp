#include "ColorverseCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
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
}

void AColorverseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(CharacterMovement))
		CharacterMovement->MaxWalkSpeed = WalkSpeed;

	InvenMgr = GetWorld()->GetSubsystem<UInventoryManager>();
	
	bIsDamageable = true;
}

void AColorverseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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
	if ((Controller != nullptr))
	{
		if(Value != 0.0f)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);

			if(!bIsRunTimer)
			{
				bIsRunTimer = true;
				GetWorldTimerManager().SetTimer(ToggleRunTimer, this, &AColorverseCharacter::SetEnabledToggleRun, AutoRunStartDelay, false);
			}
		}
		else
		{
			if(bIsRunTimer && CharacterMovement->Velocity.IsZero())
			{
				bIsRunTimer = false;
				bIsRunning = false;
				CharacterMovement->MaxWalkSpeed = WalkSpeed;
				GetWorldTimerManager().ClearTimer(ToggleRunTimer);
			}
		}
	}
}

void AColorverseCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr))
	{
		if(Value != 0.0f)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);

			if(!bIsRunTimer)
			{
				bIsRunTimer = true;
				GetWorldTimerManager().SetTimer(ToggleRunTimer, this, &AColorverseCharacter::SetEnabledToggleRun, AutoRunStartDelay, false);
			}
		}
		else
		{
			if(bIsRunTimer && CharacterMovement->Velocity.IsZero())
			{
				bIsRunTimer = false;
				bIsRunning = false;
				CharacterMovement->MaxWalkSpeed = WalkSpeed;
				GetWorldTimerManager().ClearTimer(ToggleRunTimer);
			}
		}
	}
}

void AColorverseCharacter::SetEnabledToggleRun()
{
	bIsRunning = true;
	CharacterMovement->MaxWalkSpeed = RunSpeed;
}

void AColorverseCharacter::Roll_Implementation()
{
	if(!bIsRunning || bIsRolling)
		return;

	if(CharacterMovement->IsFalling())
		return;
	
	bIsRolling = true;
	bIsDamageable = false;

	Print(1.0f, TEXT("Roll On"));
	
	GetWorldTimerManager().ClearTimer(RollTimer);
	GetWorldTimerManager().SetTimer(RollTimer, this, &AColorverseCharacter::SetDisabledRoll, RollDelay, false);
}

void AColorverseCharacter::SetDisabledRoll()
{
	bIsRolling = false;
	bIsDamageable = true;
	Print(1.0f, TEXT("Roll Off"));
}
#pragma endregion Movement

void AColorverseCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		InteractObject = Cast<AInteractObject>(OtherActor);
		if(IsValid(InteractObject))
		{
			bIsInteract = true;

			if(!bIsWatchingInteractWidget)
			{
				if(IsValid(InteractWidgetClass))
				{
					InteractWidget = Cast<UInteractWidget>(CreateWidget(GetWorld(), InteractWidgetClass));
					if(InteractWidget != nullptr)
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

void AColorverseCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		if(IsValid(InteractObject) && InteractObject == OtherActor)
		{
			InteractObject = nullptr;
			bIsInteract = false;

			if(InteractWidget != nullptr)
			{
				bIsWatchingInteractWidget = false;
				InteractWidget->RemoveFromParent();
			}
		}
	}
}

void AColorverseCharacter::Interact_Implementation()
{
	if(!bIsInteract || !IsValid(InteractObject))
		return;

	InteractObject->OnInteract();
	Print(1.0f, TEXT("Interact"));
}

void AColorverseCharacter::ControlInventory_Implementation()
{
	InvenMgr->SetInventoryUI();
}