// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BuildingInfo.h"
#include "Building.h"
#include "LimbicHUD.h"
#include "GameFramework/PlayerController.h"
#include "LimbicTestPlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ALimbicTestPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	// Timer Handles Collecting Income from All Buildings every 5 seconds
	UPROPERTY()
	FTimerHandle CollectTimer;
protected:
	// Represents if Player is on Construction Mode
	UPROPERTY(VisibleInstanceOnly)
	bool bIsConstructing= false;
	// Represents Player Current Money
	UPROPERTY()
	float Money=500.f;
	// Reference to The Building to be Constructed
	UPROPERTY()
	ABuilding* ConstructionBuildingRef;
	// Reference to The Selected Building
	UPROPERTY()
	ABuilding* SelectedBuildingRef;
	// Reference to All Constructed Buildings that gets Income
	UPROPERTY()
	TArray <ABuilding*> AllProfitableBuildings;
	// Reference to The main HUD widget 
	UPROPERTY()
	ULimbicHUD* HUD_Ref;
	// Class selector to the Main HUD widget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULimbicHUD> HUD_Class;
	// Class Selector to the Main Building spawned
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABuilding> BuildingClass;
	//
	

	// Initializes Input, Widgets, and Collecting Timer.
	virtual void BeginPlay() override;
	// Implements Collecting Money from Buildings
	UFUNCTION()
	void CollectIncome();
	// Implements Selecting Buildings
	UFUNCTION()
	void SetSelectedBuilding(ABuilding* Building);
	// Implements Unselecting Buildings
	UFUNCTION()
	void UnSetSelectedBuilding();
	// Input Bind function for LMB
	UFUNCTION()
	void Click();

public:
	// Input Bind function for RMB
	UFUNCTION()
	void Cancel();

	// Constructor to Handle Controller Initialization and Class Validation
	ALimbicTestPlayerController();
	// Tick to Handle Building following Mouse Cursor
	void Tick(float DeltaSeconds);
	// Callable Function to Add Building to All Buildings Array
	UFUNCTION()
	void AddProfitableBuilding(ABuilding* NewBuilding) 
	{ AllProfitableBuildings.Add(NewBuilding); }
	// Implements Building Selling and Destroying
	UFUNCTION()
	void SellSelectedBuilding();
	// Implements Building Spawning on Purchase
	UFUNCTION()
	void SpawnBuilding(FBuildingInfo BuildingType);
	// Checks whether the Player Is On Construction Mode
	UFUNCTION()
	bool GetIsConstructing() const { return bIsConstructing; }
};


