// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameManagers : ModuleRules
{
	public GameManagers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"UMG" , "AssetRegistry" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PrivateIncludePaths.AddRange(new string[] { "GameManagers" });

        //Add Custom Modules in Source Folder.
        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging" });
        PublicIncludePaths.AddRange(new string[] { "CustomDebugging" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameObjectPool" });
        PublicIncludePaths.AddRange(new string[] { "GameObjectPool" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameDefines" , "GameTime" });
        PublicIncludePaths.AddRange(new string[] { "GameDefines", "GameTime" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameFarm", "GameItem", "GamePuzzle" });
        PublicIncludePaths.AddRange(new string[] {  "GameFarm", "GameItem", "GamePuzzle" });

        PublicIncludePathModuleNames.AddRange(new string[] { "GameSystems" });
        PublicIncludePaths.AddRange(new string[] { "GameSystems"});

    }
}
