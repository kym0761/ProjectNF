// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameSystems : ModuleRules
{
	public GameSystems(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"UMG", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PrivateIncludePaths.AddRange(new string[] { "GameSystems" });

        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging" });
        PublicIncludePaths.AddRange(new string[] { "CustomDebugging" });

        //Add Custom Modules in Source Folder.

        PublicDependencyModuleNames.AddRange(new string[] { "GameDefines" });
        PublicIncludePaths.AddRange(new string[] { "GameDefines"});

        PublicDependencyModuleNames.AddRange(new string[] { "GameContents" });
        PublicIncludePaths.AddRange(new string[] { "GameContents" });
    }
}
