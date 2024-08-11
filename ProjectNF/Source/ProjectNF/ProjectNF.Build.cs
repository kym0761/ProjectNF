// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectNF : ModuleRules
{
	public ProjectNF(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"UMG" , "AssetRegistry" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        //모듈 자체의 경로 추가
        PrivateIncludePaths.AddRange(new string[] { "ProjectNF" });

        //Add Custom Modules in Source Folder.

        //PrivateIncludePathModuleNames.AddRange(new string[] { "CustomDebugging" });
        PrivateIncludePaths.AddRange(new string[] { "CustomDebugging" });
        PublicDependencyModuleNames.AddRange(new string[] { "CustomDebugging" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameDefines" });
        PublicIncludePaths.AddRange(new string[] { "GameDefines" });

        PublicDependencyModuleNames.AddRange(new string[] { "GamePuzzle" });
        PublicIncludePaths.AddRange(new string[] { "GamePuzzle"  });

        PublicDependencyModuleNames.AddRange(new string[] { "GameSystems"});
        PublicIncludePaths.AddRange(new string[] { "GameSystems" });

        PublicDependencyModuleNames.AddRange(new string[] { "GameContents" });
        PublicIncludePaths.AddRange(new string[] { "GameContents" });
    }
}
