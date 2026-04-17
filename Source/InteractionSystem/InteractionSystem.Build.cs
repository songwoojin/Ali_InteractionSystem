// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InteractionSystem : ModuleRules
{
	public InteractionSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"InteractionSystem",
			"InteractionSystem/Variant_Platforming",
			"InteractionSystem/Variant_Platforming/Animation",
			"InteractionSystem/Variant_Combat",
			"InteractionSystem/Variant_Combat/AI",
			"InteractionSystem/Variant_Combat/Animation",
			"InteractionSystem/Variant_Combat/Gameplay",
			"InteractionSystem/Variant_Combat/Interfaces",
			"InteractionSystem/Variant_Combat/UI",
			"InteractionSystem/Variant_SideScrolling",
			"InteractionSystem/Variant_SideScrolling/AI",
			"InteractionSystem/Variant_SideScrolling/Gameplay",
			"InteractionSystem/Variant_SideScrolling/Interfaces",
			"InteractionSystem/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
