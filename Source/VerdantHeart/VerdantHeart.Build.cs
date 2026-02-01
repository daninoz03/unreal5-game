// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VerdantHeart : ModuleRules
{
	public VerdantHeart(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"Niagara",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
