// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class IOServerTarget : TargetRules
{
       public IOServerTarget(TargetInfo Target) : base(Target)
       {
        Type = TargetType.Server;
        ExtraModuleNames.Add("IO");
       }
}