// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingInfo.h"
#include "Materials/MaterialInterface.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Building.generated.h"

// Building Visual Material Enumeration
UENUM(BlueprintType)
enum EMaterialState
{
	Normal     UMETA(DisplayName = "Normal"),
	Selected      UMETA(DisplayName = "Selected"),
	Construction   UMETA(DisplayName = "Construction"),
	Hovered   UMETA(DisplayName = "Hovered"),
	AllowedConstruction   UMETA(DisplayName = "AllowedConstruction"),
	RejectedConstruction   UMETA(DisplayName = "RejectedConstruction")
};

UCLASS()
class CITYBUILDER_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();
private:
	// Timer Handles Construction End
	UPROPERTY()
	FTimerHandle ConstructionTimer;

protected:
	// Box Collision Component
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision;
	// Building Static Mesh
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BuildingMesh;
	// Basement Static Mesh
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BasmentMesh;
	
	// Represents Building Placement state (true = Placed)
	UPROPERTY()
	bool bIsSet = false;
	// Represents Building Construction State (true = still in Construction)
	UPROPERTY()
	bool bInConstruction = true;
	// Represents If Building is Selected
	UPROPERTY()
	bool bIsSelected = false;
	// Represents Building Type Informations
	UPROPERTY()
	FBuildingInfo BuildingInfo;
	// the Main Building Material when Idle
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* NormalMaterial;
	// Material to be Applied when Selected
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* SelectedMaterial;
	// Material to be Applied On Construction
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* ConstructionMaterial;
	// Material to be Applied when Hovered by Mouse Cursor
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* HoveredMaterial;
	// Material to be Applied when Allowed to be Placed
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* AllowedMaterial;
	// Material to be Applied when Overlapping with other Object
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* RejectedMaterial;
	// Reference to Main Limbic Player Controller
	class ALimbicTestPlayerController *LimbicPC;
	// Changes Building Material depending on state
	UFUNCTION()
	void ChangeMaterial(EMaterialState State);
	// Checks Whether the Building is Overlapping other Actor
	UFUNCTION()
	bool IsOverlapping() const;
	// Called when Construction Ends
	UFUNCTION()
	void FinishedConstruction();
	// Initializes Building components and variables
	virtual void BeginPlay() override;

public:	
	// Tick to Check Overlapping before Construction
	virtual void Tick(float DeltaTime) override;
	// Getter to get Building Info
	UFUNCTION()
	FBuildingInfo GetBuildingInfo() const { return BuildingInfo; }
	// Setter to Set Building Info
	UFUNCTION()
	void SetBuildingInfo(FBuildingInfo NewBuildingInfo) { BuildingInfo = NewBuildingInfo; }
	// Implements Building Selection
	UFUNCTION()
	void SelectBuilding();
	// Implements Unselecting Building
	UFUNCTION()
	void UnSelectBuilding();
	// Implements Building Construction
	UFUNCTION()
	bool ConstructBuilding();
	// Checks if the Building can be selected
	UFUNCTION()
	bool CanBeSelected();
	// Checks if the Building can be Hovered
	UFUNCTION()
	bool CanBeHovered();
	// Implements Functionality on Mouse Hover
	UFUNCTION()
	void OnHovered(UPrimitiveComponent* TouchedComponent);
	// Implements Functionality on Mouse ends Hover
	UFUNCTION()
	void OnUnHovered(UPrimitiveComponent* TouchedComponent);
};


