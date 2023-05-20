#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
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

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UHUDWidget* HUDWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsInventoryOpen = false;

	bool GetInventoryItemByName(const FText& Name, int& Index);

	UPROPERTY()
	UDataTable* CombineDataTable;

	UPROPERTY()
	UDataTable* ItemDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TMap<FName, bool> AlreadyCombineMap;

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItem> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItem> MakerArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PaintAmount = 0.0f;

	UFUNCTION()
	void SetInventoryUI(bool IsActive, bool IsFlip = false);

	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UFUNCTION(BlueprintCallable)
	void UpdateMaker();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void AddInventoryItem(const FItem& Item, bool IsShowAcquiredUI = true);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UseInventoryItem(FItem Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UpdateMakerResultUI();
	
	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CombineItems();

	FORCEINLINE UHUDWidget* GetHUDWidget() { return HUDWidget; }
};
