// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class VRKarts : ModuleRules
{
	public VRKarts(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "PhysX", "APEX"});
        PublicAdditionalLibraries.AddRange(new string[] 
        {
            "Win64/VS2013/PhysX3CommonPROFILE_x64.lib",
            "Win64/VS2013/PhysX3CookingPROFILE_x64.lib",
            "Win64/VS2013/PhysX3ExtensionsPROFILE.lib",
            "Win64/VS2013/PhysX3PROFILE_x64.lib",
            "Win64/VS2013/PhysX3VehiclePROFILE.lib",
            "Win64/VS2013/PhysXProfileSDKPROFILE.lib",
            "Win64/VS2013/PhysXVisualDebuggerSDKPROFILE.lib",
            "Win64/VS2013/PxTaskPROFILE.lib",

            "Win32/VS2013/PhysX3CommonPROFILE_x86.lib",
            "Win32/VS2013/PhysX3CookingPROFILE_x86.lib",
            "Win32/VS2013/PhysX3ExtensionsPROFILE.lib",
            "Win32/VS2013/PhysX3PROFILE_x86.lib",
            "Win32/VS2013/PhysXProfileSDKPROFILE.lib",
            "Win32/VS2013/PhysXVisualDebuggerSDKPROFILE.lib",
            "Win32/VS2013/PxTaskPROFILE.lib",

            "Win64/VS2013/ApexFrameworkPROFILE_x64.lib",
            "Win32/VS2013/ApexFrameworkPROFILE_x86.lib"
        });             
            
        
		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }
	}
}
