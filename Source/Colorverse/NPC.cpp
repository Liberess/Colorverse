#include "NPC.h"

#include "ColorverseCharacter.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCol = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Col"));
	if(CapsuleCol)
	{
		CapsuleCol->InitCapsuleSize(34.0f, 88.0f);
		CapsuleCol->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		CapsuleCol->CanCharacterStepUpOn = ECB_No;
		CapsuleCol->SetShouldUpdatePhysicsVolume(true);
		CapsuleCol->SetCanEverAffectNavigation(false);
		CapsuleCol->bDynamicObstacle = true;
		SetRootComponent(CapsuleCol);
	}

	TriggerZone = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Zone"));
	if(TriggerZone)
	{
		TriggerZone->InitSphereRadius(120.0f);
		static FName TriggerZoneProfileName(TEXT("OverlapAllDynamic"));
		TriggerZone->SetCollisionProfileName(TriggerZoneProfileName);
		TriggerZone->SetCanEverAffectNavigation(false);
		TriggerZone->bDynamicObstacle = false;
		TriggerZone->SetupAttachment(CapsuleCol);
		TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &ANPC::OnOverlapBegin);
		TriggerZone->OnComponentEndOverlap.AddDynamic(this, &ANPC::OnOverlapEnd);
	}

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(CapsuleCol);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("NPC Mesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CapsuleCol);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTable(TEXT("/Game/DataTables/DT_Dialogue"));
	if (DataTable.Succeeded())
		DialogueDT = DataTable.Object;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(DialogueDT))
		DialogueData = *(DialogueDT->FindRow<FDialogue>(NPCName, ""));

	const FSoftClassPath DialogueRef(TEXT("/Game/UI/BP_Dialogue.BP_Dialogue_C"));
	DialogueWidgetRef = DialogueRef.TryLoadClass<UDialogueWidget>();

	const FSoftClassPath InteractRef(TEXT("/Game/UI/BP_InteractWidget.BP_InteractWidget_C"));
	InteractWidgetRef = InteractRef.TryLoadClass<UInteractWidget>();
}

void ANPC::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (InteractWidgetRef != nullptr)
		{
			if(InteractWidget == nullptr)
				InteractWidget = Cast<UInteractWidget>(CreateWidget(GetWorld(), InteractWidgetRef));
			
			InteractWidget->SetInteractText( FText::FromName(FName(TEXT("대화하기"))));
			InteractWidget->AddToViewport();
		}
	}
}

void ANPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		static AColorverseCharacter* Character = Cast<AColorverseCharacter>(OtherActor);
		if(IsValid(Character))
		{
			if(DialogueWidget != nullptr)
			{
				TalkIndex = 0;
				DialogueWidget->RemoveFromParent();
			}

			if(InteractWidget != nullptr)
				InteractWidget->RemoveFromParent();
		}
	}
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANPC::OnTalk_Implementation()
{
	IIDialogue::OnTalk_Implementation();

	++TalkIndex;

	if(TalkIndex < DialogueData.Dialogues.Num())
	{
		if(DialogueWidget == nullptr)
			DialogueWidget = Cast<UDialogueWidget>(CreateWidget(GetWorld(), DialogueWidgetRef));
		
		DialogueWidget->AddToViewport();
		DialogueWidget->SetDialogueText(
			FText::FromName(NPCName),
			DialogueData.Dialogues[TalkIndex]);
	}
	else
	{
		TalkIndex = -1;
		DialogueWidget->RemoveFromParent();
		InteractWidget->RemoveFromParent();
	}
}
