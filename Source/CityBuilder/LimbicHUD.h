// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "BuildingButton.h"
#include "Blueprint/UserWidget.h"
#include "LimbicHUD.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API ULimbicHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	// All Buildings Data table Reference
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingsDatatable;
	// UMG Building Button Class to fill the list with
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBuildingButton> Button_Class;
	// Implements Selling Selected Building
	UFUNCTION()
	void OnClicked();
	
public:
	// Constructor to Validate Data table & Button Class
	ULimbicHUD(const FObjectInitializer& ObjectInitializer);
	// Represents Selected Building Name
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
	// Represents Selected Building Details
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Info;
	// Represents Selected Building Income Rate
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Income;
	// Represents Selected Building Money when Sold
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SellText;
	// Represents Player Current Money
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MoneyText;
	// Button to Implement Selling Building
	UPROPERTY(meta = (BindWidget))
	class UButton* Sell;
	// Represents Selected Building Image
	UPROPERTY(meta = (BindWidget))
	class UImage* HouseImg;
	// Main List of All Building types to Buy from
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ListOfBuildings;
	// Container for Selected Building Info
	UPROPERTY(meta = (BindWidget))
	class UBorder* BuildingInfo;
	
	// Initializes HUD and List of Buildings from Data table
	bool Initialize();
	// Updates & Shows the Container of Selected Building
	UFUNCTION()
	void ShowBuildingInfo(FBuildingInfo Building);
	// Hides the Info Container
	UFUNCTION()
	void HideBuildingInfo();
	// Updates Current Money Text
	UFUNCTION()
	void UpdateMoney(float Money);	
};
