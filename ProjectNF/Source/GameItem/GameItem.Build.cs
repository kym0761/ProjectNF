// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameItem : ModuleRules
{
	public GameItem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        PrivateIncludePaths.AddRange(new string[] { "GameItem" });

      
        PrivateDependencyModuleNames.AddRange(new string[] {  "GameDefines" });
        PrivateIncludePaths.AddRange(new string[] {  "GameDefines" });

        //PrivateDependencyModuleNames.AddRange(new string[] { "ProjectNF"});
        //PrivateIncludePaths.AddRange(new string[] { "ProjectNF" });

        PublicIncludePathModuleNames.AddRange(new string[] { "CustomDebugging" });
        PublicIncludePaths.AddRange(new string[] { "CustomDebugging" });
    }
}
