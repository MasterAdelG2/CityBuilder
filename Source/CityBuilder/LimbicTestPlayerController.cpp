// Copyright Epic Games, Inc. All Rights Reserved.

#include "LimbicTestPlayerController.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "UObject/ConstructorHelpers.h"

ALimbicTestPlayerController::ALimbicTestPlayerController()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bAllowTickBeforeBeginPlay = false;
	SetActorTickInterval(0.05f);
	//
	if (!IsValid(HUD_Class))
	{
		static ConstructorHelpers::FClassFinder<ULimbicHUD> BP_HUD_Class(TEXT("/Game/Blueprints/BP_HUD"));
		HUD_Class = BP_HUD_Class.Class;
	}
	if (!IsValid(BuildingClass))
	{
		static ConstructorHelpers::FClassFinder<ABuilding> BP_Building_Class(TEXT("/Game/Blueprints/BP_Building"));
		BuildingClass = BP_Building_Class.Class;
	}
}

void ALimbicTestPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//
	if (bIsConstructing)
	{
		FHitResult MouseHit;
		TArray <TEnumAsByte<EObjectTypeQuery>> Objects;
		Objects.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		bool success= GetHitResultUnderCursorForObjects(Objects, false, MouseHit);
		if (success)
		{
			ConstructionBuildingRef->SetActorLocation(MouseHit.ImpactPoint,true);
		}
	}
}

void ALimbicTestPlayerController::SellSelectedBuilding()
{
	AllProfitableBuildings.Remove(SelectedBuildingRef);
	Money += SelectedBuildingRef->GetBuildingInfo().Price / 2;
	HUD_Ref->UpdateMoney(Money);
	SelectedBuildingRef->Destroy();
}

void ALimbicTestPlayerController::SpawnBuilding(FBuildingInfo BuildingType)
{
	if (Money >= BuildingType.Price)
	{
		UnSetSelectedBuilding();
		FTransform transform = FTransform::Identity;
		ConstructionBuildingRef = GetWorld()->SpawnActorDeferred<ABuilding>(BuildingClass, transform, this);
		ConstructionBuildingRef->SetBuildingInfo(BuildingType);
		ConstructionBuildingRef->FinishSpawning(transform);
		bIsConstructing = true;
	}
}

// Called when the game starts or when spawned
void ALimbicTestPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//
	InputComponent->BindAction("Click", IE_Pressed, this, &ALimbicTestPlayerController::Click);
	InputComponent->BindAction("Cancel", IE_Pressed, this, &ALimbicTestPlayerController::Cancel);
	//
	HUD_Ref = Cast<ULimbicHUD>(CreateWidget(this, HUD_Class));
	if (IsValid(HUD_Ref))
	{
		HUD_Ref->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(CollectTimer, this, &ALimbicTestPlayerController::CollectIncome, 5.0f, true);
}

void ALimbicTestPlayerController::CollectIncome()
{
	for (ABuilding* Building : AllProfitableBuildings)
	{
		Money += Building->GetBuildingInfo().IncomeRate;
	}
	HUD_Ref->UpdateMoney(Money);
}

void ALimbicTestPlayerController::SetSelectedBuilding(ABuilding* Building)
{
	SelectedBuildingRef = Building;
	SelectedBuildingRef->SelectBuilding();
	HUD_Ref->ShowBuildingInfo(Building->GetBuildingInfo());
}

void ALimbicTestPlayerController::UnSetSelectedBuilding()
{
	if (SelectedBuildingRef)
	{
		SelectedBuildingRef->UnSelectBuilding();
		SelectedBuildingRef = nullptr;
		HUD_Ref->HideBuildingInfo();
	}
}

void ALimbicTestPlayerController::Click()
{
	FHitResult MouseHit;
	bool success = GetHitResultUnderCursor(ECC_Visibility, false, MouseHit);
	if (bIsConstructing)
	{
		if (success)
		{
			if (ConstructionBuildingRef->ConstructBuilding())
			{
				Money -= ConstructionBuildingRef->GetBuildingInfo().Price;
				HUD_Ref->UpdateMoney(Money);
				bIsConstructing = false;
				ConstructionBuildingRef = nullptr;
			}
		}
		else
		{
			Cancel();
		}
	}
	else
	{
		UnSetSelectedBuilding();
		ABuilding* TargetedBuilding= Cast<ABuilding>(MouseHit.Actor);
		if (TargetedBuilding != nullptr)
		{
			if (TargetedBuilding->CanBeSelected())
			{
				SetSelectedBuilding(TargetedBuilding);
			}
		}
	}
}

void ALimbicTestPlayerController::Cancel()
{
	if (bIsConstructing)
	{
		ConstructionBuildingRef->Destroy();
		bIsConstructing = false;
	}
	else
	{
		UnSetSelectedBuilding();
	}
}
