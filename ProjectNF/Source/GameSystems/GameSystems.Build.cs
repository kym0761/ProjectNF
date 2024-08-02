// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameSystems : ModuleRules
{
	public GameSystems(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PrivateIncludePaths.AddRange(new string[] { "GameSystems" });

        PrivateIncludePathModuleNames.AddRange(new string[] { "CustomDebugging" });
        PrivateIncludePaths.AddRange(new string[] { "CustomDebugging" });
        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging" });

        //Add Custom Modules in Source Folder.
        PublicDependencyModuleNames.AddRange(new string[] { "GameFarm", "GameItem", "GamePuzzle" });
        PublicIncludePaths.AddRange(new string[] {  "GameFarm", "GameItem", "GamePuzzle" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameDefines" });
        PublicIncludePaths.AddRange(new string[] { "GameDefines" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameManagers" });
        PublicIncludePaths.AddRange(new string[] { "GameManagers" });

        PublicIncludePathModuleNames.AddRange(new string[] { "GameTime" });
        PublicIncludePaths.AddRange(new string[] { "GameTime" });
    }
}
