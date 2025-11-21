// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class MyProject1120EditorTarget : TargetRules
{
	public MyProject1120EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

        //BuildEnvironment = TargetBuildEnvironment.Unique;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
        //bOverrideBuildEnvironment = true;

        ExtraModuleNames.AddRange( new string[] { "MyProject1120" } );
	}
}
