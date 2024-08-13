// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CppDeveloperTestTask : ModuleRules
{
	public CppDeveloperTestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ProceduralMeshComponent", "GeometryScriptingEditor", "PhysicsCore" });
	}
}
