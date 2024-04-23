// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MentoramaCPP5 : ModuleRules
{
	public MentoramaCPP5(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
