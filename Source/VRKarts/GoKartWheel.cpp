// Fill out your copyright notice in the Description page of Project Settings.

#include "VRKarts.h"
#include "GoKartWheel.h"

float UGoKartWheel::GetWheelLongSlip()
{
	return DebugLongSlip;
}

float UGoKartWheel::GetWheelLatSlip()
{
	return DebugLatSlip;
}

float UGoKartWheel::GetWheelNormalizedTireLoad()
{
	return DebugNormalizedTireLoad;
}

float UGoKartWheel::GetWheelTorque()
{
	return DebugWheelTorque;
}

float UGoKartWheel::GetWheelLongForce()
{
	return DebugLongForce;
}

float UGoKartWheel::GetWheelLatForce()
{
	return DebugLatForce;
}

FVector UGoKartWheel::GetWheelLocation()
{
	return Location;
}

FVector UGoKartWheel::GetWheelOldLocation()
{
	return OldLocation;
}

FVector UGoKartWheel::GetWheelVelocity()
{
	return Velocity;
}

