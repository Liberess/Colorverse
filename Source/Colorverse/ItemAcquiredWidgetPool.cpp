#include "ItemAcquiredWidgetPool.h"
#include "Kismet/GameplayStatics.h"

UItemAcquiredWidgetPool::UItemAcquiredWidgetPool()
{
	
}

UUserWidget* UItemAcquiredWidgetPool::GetOrCreateWidget(UObject* WorldContextObject, TSubclassOf<UUserWidget> WidgetClass)
{
	if (!WidgetClass)
		return nullptr;

	FWidgetData* FoundWidgetData = PoolMap.Find(WidgetClass);

	if (!FoundWidgetData)
	{
		FWidgetData NewWidgetData;
		NewWidgetData.WidgetClass = WidgetClass;
		PoolMap.Add(WidgetClass, NewWidgetData);
		FoundWidgetData = PoolMap.Find(WidgetClass);
	}

	for (UUserWidget* Widget : FoundWidgetData->WidgetArray)
	{
		if (Widget && !Widget->IsVisible())
			return Widget;
	}

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World)
		return nullptr;

	UUserWidget* NewWidget = CreateWidget<UUserWidget>(World, WidgetClass);
	FoundWidgetData->WidgetArray.Add(NewWidget);
	return NewWidget;
}

void UItemAcquiredWidgetPool::ReleaseWidget(UUserWidget* Widget)
{
	if (Widget != nullptr)
		return;

	const TSubclassOf<UUserWidget> WidgetClass = Widget->GetClass();
	const FWidgetData* FoundWidgetData = PoolMap.Find(WidgetClass);

	if (!FoundWidgetData)
		return;

	Widget->SetVisibility(ESlateVisibility::Collapsed);
}
