// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectNFTarget : TargetRules
{
	public ProjectNFTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.Add("ProjectNF");
        ExtraModuleNames.Add("GamePuzzle");
        ExtraModuleNames.Add("GameFarm");
        ExtraModuleNames.Add("GameItem");
        ExtraModuleNames.Add("GameTime");
    }
}
