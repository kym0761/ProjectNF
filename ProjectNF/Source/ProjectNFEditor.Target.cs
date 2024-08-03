// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectNFEditorTarget : TargetRules
{
	public ProjectNFEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

        //Main
        ExtraModuleNames.Add("ProjectNF");

        //Debugging & Data Defines
        ExtraModuleNames.Add("CustomDebugging");
        ExtraModuleNames.Add("GameDefines");

        //Gamesystems And Managers
        ExtraModuleNames.Add("GameSystems");

        //Contents
        ExtraModuleNames.Add("GamePuzzle");
        ExtraModuleNames.Add("GameContents");
    }
}
