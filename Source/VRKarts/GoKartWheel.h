// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Vehicles/VehicleWheel.h"
#include "GoKartWheel.generated.h"


UCLASS(BlueprintType, Blueprintable)
class VRKARTS_API UGoKartWheel : public UVehicleWheel
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")	
		float GetWheelLongSlip();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetWheelLatSlip();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetWheelNormalizedTireLoad();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetWheelTorque();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetWheelLongForce();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		float GetWheelLatForce();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		FVector GetWheelLocation();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		FVector GetWheelOldLocation();

	UFUNCTION(BlueprintCallable, Category = "Game|Components|WheeledVehicleMovement")
		FVector GetWheelVelocity ();
};
