// Fill out your copyright notice in the Description page of Project Settings.

#include "VRKarts.h"
#include "Runtime/Engine/Private/EnginePrivate.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PhysicsPublic.h"
#include "CustomVehicleWheel.h"
#include "Vehicles/WheeledVehicleMovementComponent.h"
#include "Vehicles/TireType.h"

#if WITH_PHYSX
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "Runtime/Engine/Private/Vehicles/PhysXVehicleManager.h"
#endif // WITH_PHYSX


UCustomVehicleWheel::UCustomVehicleWheel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CollisionMeshObj(TEXT("/Engine/EngineMeshes/Cylinder"));
	CollisionMesh = CollisionMeshObj.Object;

	static ConstructorHelpers::FObjectFinder<UTireType> TireTypeObj(TEXT("/Engine/EngineTireTypes/DefaultTireType"));
	TireType = TireTypeObj.Object;

	ShapeRadius = 30.0f;
	ShapeWidth = 10.0f;
	bAutoAdjustCollisionSize = true;
	Mass = 20.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 70.0f;
	MaxBrakeTorque = 1500.f;
	MaxHandBrakeTorque = 3000.f;
	DampingRate = 0.25f;
	LatStiffMaxLoad = 2.0f;
	LatStiffValue = 17.0f;
	LongStiffValue = 1000.0f;
	SuspensionForceOffset = 0.0f;
	SuspensionMaxRaise = 10.0f;
	SuspensionMaxDrop = 10.0f;
	SuspensionNaturalFrequency = 7.0f;
	SuspensionDampingRatio = 1.0f;
}

float UCustomVehicleWheel::GetSteerAngle()
{
#if WITH_VEHICLE
	return FMath::RadiansToDegrees(VehicleSim->GetWorld()->GetPhysicsScene()->GetVehicleManager()->GetWheelsStates(VehicleSim)[WheelIndex].steerAngle);
#else
	return 0.0f;
#endif // WITH_PHYSX
}

float UCustomVehicleWheel::GetRotationAngle()
{
#if WITH_VEHICLE
	float RotationAngle = -1.0f * FMath::RadiansToDegrees(VehicleSim->PVehicle->mWheelsDynData.getWheelRotationAngle(WheelIndex));
	check(!FMath::IsNaN(RotationAngle));
	return RotationAngle;
#else
	return 0.0f;
#endif // WITH_PHYSX
}

float UCustomVehicleWheel::GetSuspensionOffset()
{
#if WITH_VEHICLE
	return VehicleSim->GetWorld()->GetPhysicsScene()->GetVehicleManager()->GetWheelsStates(VehicleSim)[WheelIndex].suspJounce;
#else
	return 0.0f;
#endif // WITH_PHYSX
}

#if WITH_PHYSX

void UCustomVehicleWheel::Init(UWheeledVehicleMovementComponent* InVehicleSim, int32 InWheelIndex)
{
	check(InVehicleSim);
	check(InVehicleSim->Wheels.IsValidIndex(InWheelIndex));

	VehicleSim = InVehicleSim;
	WheelIndex = InWheelIndex;
	WheelShape = NULL;

#if WITH_VEHICLE
	const int32 WheelShapeIdx = VehicleSim->PVehicle->mWheelsSimData.getWheelShapeMapping(WheelIndex);
	check(WheelShapeIdx >= 0);

	VehicleSim->PVehicle->getRigidDynamicActor()->getShapes(&WheelShape, 1, WheelShapeIdx);
	check(WheelShape);
#endif

	Location = GetPhysicsLocation();
	OldLocation = Location;
}

void UCustomVehicleWheel::Shutdown()
{
	WheelShape = NULL;
}

FWheelSetup& UCustomVehicleWheel::GetWheelSetup()
{
	return VehicleSim->WheelSetups[WheelIndex];
}

void UCustomVehicleWheel::Tick(float DeltaTime)
{
	OldLocation = Location;
	Location = GetPhysicsLocation();
	Velocity = (Location - OldLocation) / DeltaTime;
}

FVector UCustomVehicleWheel::GetPhysicsLocation()
{
#if WITH_VEHICLE
	if (WheelShape)
	{
		PxVec3 PLocation = VehicleSim->PVehicle->getRigidDynamicActor()->getGlobalPose().transform(WheelShape->getLocalPose()).p;
		return P2UVector(PLocation);
	}
#endif

	return FVector(0.0f);
}

#if WITH_EDITOR

void UCustomVehicleWheel::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Trigger a runtime rebuild of the PhysX vehicle
	FPhysXVehicleManager::VehicleSetupTag++;
}

#endif //WITH_EDITOR

#endif // WITH_PHYSX

UPhysicalMaterial* UCustomVehicleWheel::GetContactSurfaceMaterial()
{
	UPhysicalMaterial* PhysMaterial = NULL;

#if WITH_VEHICLE
	const PxMaterial* ContactSurface = VehicleSim->GetWorld()->GetPhysicsScene()->GetVehicleManager()->GetWheelsStates(VehicleSim)[WheelIndex].tireSurfaceMaterial;
	if (ContactSurface)
	{
		PhysMaterial = FPhysxUserData::Get<UPhysicalMaterial>(ContactSurface->userData);
	}
#endif

	return PhysMaterial;
}

