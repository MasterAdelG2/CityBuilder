// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "LimbicTestPlayerController.h"

// Sets default values
ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.1f);
	// Setting Components Tree
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->AddLocalOffset(FVector(0, 0,35));
	RootComponent = BoxCollision;
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
	BuildingMesh->SetupAttachment(RootComponent);
	BasmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasmentMesh"));
	BasmentMesh->AddLocalOffset(FVector(0, 0, -24.9));
	BasmentMesh->SetupAttachment(BuildingMesh);
}

void ABuilding::ChangeMaterial(EMaterialState State)
{
	// Temp Array to be used with the Enumeration States
	TArray <UMaterialInterface*> TempAllMaterials = { NormalMaterial, SelectedMaterial, ConstructionMaterial, HoveredMaterial, AllowedMaterial, RejectedMaterial };

	BuildingMesh->SetMaterial(0, TempAllMaterials[State]);
}

bool ABuilding::IsOverlapping() const
{
	TArray<AActor*> AllActors;
	BoxCollision->GetOverlappingActors(AllActors);
	return (AllActors.Num() > 1);
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	if (!bIsSet)
	{
		if (IsOverlapping())
		{
			ChangeMaterial(RejectedConstruction);
		}
		else
		{
			ChangeMaterial(AllowedConstruction);
		}
	}
}

void ABuilding::SelectBuilding()
{
	if (CanBeSelected())
	{
		bIsSelected = true;
		ChangeMaterial(Selected);
	}
}

void ABuilding::UnSelectBuilding()
{
	bIsSelected = false;
	ChangeMaterial(Normal);
}

bool ABuilding::ConstructBuilding()
{
	if (IsOverlapping())
	{
		return false;
	}
	bIsSet = true;
	bInConstruction = true;
	SetActorTickEnabled(false);
	ChangeMaterial(Construction);
	GetWorldTimerManager().SetTimer(ConstructionTimer, this, &ABuilding::FinishedConstruction, BuildingInfo.BuildingTime, false);
	return true;
}

void ABuilding::FinishedConstruction()
{
	bInConstruction = false;
	ChangeMaterial(Normal);
	if (LimbicPC != nullptr)
	{
		LimbicPC->AddProfitableBuilding(this);
	}
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	//
	LimbicPC = Cast<ALimbicTestPlayerController>(GetOwner());
	//
	if (BuildingInfo.Model3D)
	{
		BuildingMesh->SetStaticMesh(BuildingInfo.Model3D);
		BoxCollision->SetBoxExtent(FVector(BuildingInfo.Size.X, BuildingInfo.Size.Y, 35.f));
		BasmentMesh->SetWorldScale3D(FVector(BuildingInfo.Size.X * 0.02f, BuildingInfo.Size.Y * 0.02f, 0.5f));
		BuildingMesh->OnBeginCursorOver.AddDynamic(this, &ABuilding::OnHovered);
		BuildingMesh->OnEndCursorOver.AddDynamic(this, &ABuilding::OnUnHovered);
	}
}

bool ABuilding::CanBeSelected()
{
	return (!bInConstruction && bIsSet);
}

bool ABuilding::CanBeHovered()
{
	return (!bIsSelected && !bInConstruction && bIsSet && !LimbicPC->GetIsConstructing());
}

void ABuilding::OnHovered(UPrimitiveComponent* TouchedComponent)
{
	if (CanBeHovered())
	{
		ChangeMaterial(Hovered);
	}
}

void ABuilding::OnUnHovered(UPrimitiveComponent* TouchedComponent)
{
	if (CanBeHovered())
	{
		ChangeMaterial(Normal);
	}
}

