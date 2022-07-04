// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingButton.h"
#include "LimbicTestPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UBuildingButton::InitializeUI(FBuildingInfo Info)
{
	BuildingButton->OnClicked.AddDynamic(this, &UBuildingButton::OnClicked);
	//
	BuildingInfo = Info;
	Name->SetText(BuildingInfo.Name);
	Price->SetText(FText::FromString( FString::Printf(TEXT("%i$"), BuildingInfo.Price)));
	BuildingIMG->SetBrushFromTexture(BuildingInfo.BuildingImage, false);
}

void UBuildingButton::OnClicked()
{
	ALimbicTestPlayerController* LimbicPC= Cast<ALimbicTestPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	if (LimbicPC != nullptr)
	{
		if (LimbicPC->GetIsConstructing())
		{
			LimbicPC->Cancel();
		}
		LimbicPC->SpawnBuilding(BuildingInfo);
	}
}
