// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "Blueprint/UserWidget.h"
#include "BuildingButton.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDER_API UBuildingButton : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// Building Information
	UPROPERTY()
	FBuildingInfo BuildingInfo;
	// Purchase Implementation
	UFUNCTION()
	void OnClicked();

public:
	// Represents Building Name
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
	// Represents Building Price
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Price;
	// The Button to Purchase the Building
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildingButton;
	// Represents Building 2D Image
	UPROPERTY(meta = (BindWidget))
	class UImage* BuildingIMG;
	// Callable Initialize Function to pass parameters to Widget
	UFUNCTION()
	void InitializeUI(FBuildingInfo Info);
};
