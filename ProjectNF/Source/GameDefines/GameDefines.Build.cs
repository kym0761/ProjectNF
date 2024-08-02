// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameDefines : ModuleRules
{
	public GameDefines(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        PrivateIncludePaths.AddRange(new string[] { "GameDefines" });

        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging"});
    }
}
