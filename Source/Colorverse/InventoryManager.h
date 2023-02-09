#pragma once

#include "CoreMinimal.h"
#include "IItem.h"
#include "InventoryWidget.h"
#include "Subsystems/WorldSubsystem.h"
#include "InventoryManager.generated.h"

UCLASS()
class COLORVERSE_API UInventoryManager : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FItem> InventoryArray;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsInventoryOpen;

	bool GetInventoryItemByName(const FText& Name, int& Index);
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();

	void SetInventoryUI();

	FItem GetInventoryItem(int Index) { return InventoryArray[Index]; }
	void SetInventoryItem(int Index);
	void SetInventoryItem(int Index, const FItem& Item);

	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void AddInventoryItem(const FItem& Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UseInventoryItem(FItem Item);
};
