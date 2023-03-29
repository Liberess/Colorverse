#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
#include "IItem.h"
#include "InventoryWidget.h"
#include "MakerWidget.h"
#include "StatueWidget.h"
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
	UMakerWidget* MakerWidget;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStatueWidget* StatueWidget;
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UHUDWidget* HUDWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsInventoryOpen = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsMakerOpen = false;

	bool GetInventoryItemByName(const FText& Name, int& Index);

	UPROPERTY()
	UDataTable* CombineDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float GetCombinePaintAmount = 30.0f;
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FItem> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TArray<FItem> MakerArray;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<float> PaintAmountArray;

	UFUNCTION()
	void SetInventoryUI();
	
	UFUNCTION()
	void SetMakerUI();
	
	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UFUNCTION(BlueprintCallable)
	void UpdateMaker();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void AddInventoryItem(const FItem& Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UseInventoryItem(FItem Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CombineItems();
};
