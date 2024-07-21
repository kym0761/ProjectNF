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
		ExtraModuleNames.Add("ProjectNF");

        ExtraModuleNames.Add("GamePuzzle");
        ExtraModuleNames.Add("GameFarm");
        ExtraModuleNames.Add("GameItem");
        ExtraModuleNames.Add("GameTime");
        ExtraModuleNames.Add("GameObjectPool");
        ExtraModuleNames.Add("GameDefines");
        ExtraModuleNames.Add("CustomDebugging");
    }
}
