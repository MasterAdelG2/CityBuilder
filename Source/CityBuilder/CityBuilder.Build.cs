// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CityBuilder : ModuleRules
{
	public CityBuilder(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "UMG" });
	}
}
