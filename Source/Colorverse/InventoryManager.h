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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsStatueOpen = false;

	bool GetInventoryItemByName(const FText& Name, int& Index);

	UPROPERTY()
	UDataTable* CombineDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	float GetCombinePaintAmount = 30.0f;
	
public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void InitializeManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItem> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItem> MakerArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItem> StatueArray;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AStatue*> Statues;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float PaintAmount = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AStatue* CurrentStatue;

	UFUNCTION()
	void SetInventoryUI(bool IsActive, bool IsFlip = false);
	
	UFUNCTION()
	void SetMakerUI(bool IsActive, bool IsFlip = false);

	UFUNCTION()
	void SetStatueUI(bool IsActive, bool IsUnlockPanel = true);
	
	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UFUNCTION(BlueprintCallable)
	void UpdateMaker();
	
	UFUNCTION(BlueprintCallable)
	void UpdateStatue();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void AddInventoryItem(const FItem& Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void UseInventoryItem(FItem Item);

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void CombineItems();

	UFUNCTION(BlueprintCallable, Category=Statue)
	void SacrificeItems(ESacrificeType SacrificeType);
	
	UFUNCTION(BlueprintCallable, Category=Statue)
	void IncreaseStatueColorRecoveryProgress(ECombineColors SacrificeColor, float Amount);
	
	UFUNCTION(BlueprintCallable, Category=Statue)
	void UpdateStatueUI();
	
	FORCEINLINE UHUDWidget* GetHUDWidget() { return HUDWidget; }
};
