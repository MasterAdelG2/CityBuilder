// Fill out your copyright notice in the Description page of Project Settings.


#include "LimbicHUD.h"
#include "BuildingInfo.h"
#include "Kismet/GameplayStatics.h"
#include "LimbicTestPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/Border.h"

ULimbicHUD::ULimbicHUD(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	
	if (!IsValid(Button_Class))
	{
		static ConstructorHelpers::FClassFinder<UBuildingButton> BP_Button_Class(TEXT("/Game/Blueprints/BP_BuildingButton"));
		if (!ensure(BP_Button_Class.Class != nullptr)) return;
		Button_Class = BP_Button_Class.Class;
	}
	//
	if (!IsValid(BuildingsDatatable))
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Main_Datatable(TEXT("/Game/DataTables/BuildingTypes"));
		if (Main_Datatable.Succeeded())
		{
			BuildingsDatatable = Main_Datatable.Object;
		}
	}
}

bool ULimbicHUD::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	//
	Sell->OnClicked.AddDynamic(this, &ULimbicHUD::OnClicked);
	//
	TArray<FName> AllRowNames = BuildingsDatatable->GetRowNames();
	for (FName RowName : AllRowNames)
	{
		FBuildingInfo* Temp_Info = BuildingsDatatable->FindRow<FBuildingInfo>(RowName, "");
		UBuildingButton* Temp_Button = Cast<UBuildingButton>(CreateWidget(this, Button_Class));
		Temp_Button->InitializeUI(*Temp_Info);
		ListOfBuildings->AddChild(Temp_Button);
	}
	return true;
}

void ULimbicHUD::OnClicked()
{
	ALimbicTestPlayerController* LimbicPC = Cast<ALimbicTestPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (LimbicPC != nullptr)
	{
		LimbicPC->SellSelectedBuilding();
		HideBuildingInfo();
	}
}

void ULimbicHUD::ShowBuildingInfo(FBuildingInfo Building)
{
	Name->SetText(Building.Name);
	Info->SetText(Building.Details);
	Income->SetText(FText::FromString(FString::Printf(TEXT("Income: %i$"), Building.IncomeRate)));
	SellText->SetText(FText::FromString(FString::Printf(TEXT("Sell for: %i$"), Building.Price/2)));
	HouseImg->SetBrushFromTexture(Building.BuildingImage, false);
	BuildingInfo->SetVisibility(ESlateVisibility::Visible);
}

void ULimbicHUD::HideBuildingInfo()
{
	BuildingInfo->SetVisibility(ESlateVisibility::Hidden);
}

void ULimbicHUD::UpdateMoney(float Money)
{
	MoneyText->SetText(FText::FromString(FString::Printf(TEXT("Money: %i$"), (int32)Money)));
}
