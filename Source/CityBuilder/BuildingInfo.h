// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "BuildingInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CITYBUILDER_API FBuildingInfo : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Details;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 IncomeRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* BuildingImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Model3D;
	

};
