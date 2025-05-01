// Shoot Then Up Game, All Rights Reserved

using UnrealBuildTool;

public class ShooterGame : ModuleRules
{
	public ShooterGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"ShooterGame/Public/Player", 
			"ShooterGame/Public/Services",
			"ShooterGame/Public/Config", 
			"ShooterGame/Public/Helpers",
			"ShooterGame/Public/Component",
			"ShooterGame/Public/Services/EventBus",
			"ShooterGame/Public/Dev/",
			"ShooterGame/Public/Dev/DamageType",
			"ShooterGame/Public/Weapon",
			"ShooterGame/Public/UI",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
