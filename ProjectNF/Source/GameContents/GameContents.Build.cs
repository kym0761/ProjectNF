// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameContents : ModuleRules
{
	public GameContents(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PrivateIncludePaths.AddRange(new string[] { "GameContents" });

        //Add Modules
        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging" });
        PublicIncludePaths.AddRange(new string[] { "CustomDebugging" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameDefines" });
        PublicIncludePaths.AddRange(new string[] { "GameDefines" });

        PublicDependencyModuleNames.AddRange(new string[] { "ProjectNF" });
        CircularlyReferencedDependentModules.AddRange(new string[] { "ProjectNF" });
        PublicIncludePaths.AddRange(new string[] { "ProjectNF" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameSystems" });
        CircularlyReferencedDependentModules.AddRange(new string[] { "GameSystems" });
        PublicIncludePaths.AddRange(new string[] { "GameSystems" });

    }
}
