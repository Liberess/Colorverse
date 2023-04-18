#include "ItemAcquiredWidget.h"
#include "HUDWidget.h"

void UItemAcquiredWidget::UpdateItemInformation(const FItem& ItemData)
{
	ItemImg->SetBrushFromTexture(ItemData.IconImg);
	ItemNameTxt->SetText(ItemData.Name);
	ItemAmountTxt->SetText(FText::FromString("x" + FString::FromInt(ItemData.Amount)));
	PlayAnimation(ShowAnim);

	GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
	GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
	{
		if (LogIndex >= 4)
			return;

		StopAnimation(ShowAnim);
		PlayAnimation(HideAnim);

		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, FTimerDelegate::CreateLambda([&]()
		{
			ReleaseItemLogWidget();
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("auto release"));
		}), 1.0f, false);
	}, 2.0f, false);
}

void UItemAcquiredWidget::UpdateItemLogIndex()
{
	++LogIndex;
	if (LogIndex >= 4)
	{
		StopAnimation(ShowAnim);
		PlayAnimation(HideAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);
		GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("over 4"));
			ReleaseItemLogWidget();
		}, 1.0f, false);
	}
	else if (LogIndex >= 3)
	{
		//StopAnimation(ShowAnim);
		GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
		GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer, [this]()
		{
			if (LogIndex >= 4)
				return;


			StopAnimation(ShowAnim);
			PlayAnimation(HideAnim, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.5f);

			GetWorld()->GetTimerManager().SetTimer(RemoveLogTimer,
			                                       FTimerDelegate::CreateUObject(
				                                       this, &UItemAcquiredWidget::ReleaseItemLogWidget), 1.0f,
			                                       false);
		}, 1.0f, false);
	}
}

void UItemAcquiredWidget::ReleaseItemLogWidget()
{
	SetVisibility(ESlateVisibility::Collapsed);
	const FSoftClassPath WidgetClassRef(TEXT("/Script/HUDWidget.HUDWidget_C"));
	if (UClass* WidgetClass = WidgetClassRef.TryLoadClass<UItemAcquiredWidget>())
	{
		if (UHUDWidget* HUDWidget = Cast<UHUDWidget>(WidgetClass))
			HUDWidget->ReleaseItemLogWidget(this);
	}

	GetWorld()->GetTimerManager().ClearTimer(RemoveLogTimer);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("release"));
}
