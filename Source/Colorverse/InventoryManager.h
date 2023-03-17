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
	UInventoryManager();
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UInventoryWidget* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsInventoryOpen;

	bool GetInventoryItemByName(const FText& Name, int& Index);

	UPROPERTY()
	UDataTable* CombineDataTable;
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FItem> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FItem> MakerArray;
	
	void SetInventoryUI();

	UFUNCTION(BlueprintCallable)
	void UpdateInventory(bool IsMaker);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void AddInventoryItem(const FItem& Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UseInventoryItem(FItem Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CombineItems();
};
