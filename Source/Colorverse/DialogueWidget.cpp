#include "DialogueWidget.h"

void UDialogueWidget::SetDialogueText(FText Name, FText Dialogue)
{
	NPCNameTxt->SetText(Name);
	DialogueTxt->SetText(Dialogue);
}
