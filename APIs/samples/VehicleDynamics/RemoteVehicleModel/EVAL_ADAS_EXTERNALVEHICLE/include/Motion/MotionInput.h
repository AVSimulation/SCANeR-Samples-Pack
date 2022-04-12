
#pragma once

#include "stk/Mark.h"
#include "Motion/MotionEnums.h"

namespace mc {

struct ITNProperty
{
	int laneType;
	int groundIndex;
	int groundType;
	double groundGrip;
	double roughnessHeight;
	double roughnessLength;
	double roughnessHeightStdDeviation;
	double roughnessLengthStdDeviation;
};

struct Frequency
{
	double frequency;
	stk::Vector3 amplitude;
};

struct MotionInput
{
	stk::Mark position;
	stk::Mark speed;
	stk::Mark acceleration;
	double groundPitch;
	double groundRoll;
	ITNProperty groundProperty[4];
	Frequency noiseInput[10];
	double specialEffects[5];
	stk::Mark platformOffset;
	stk::Vector3 linearActuatorsOffset;
	double rollActuatorOffset;
	double pitchActuatorOffset;
	double yawActuatorOffset;

	mc::VehiclePlayerState	vehiclePlayerCommand;
	mc::VehiclePlayerState	vehiclePlayerState;

	double custom[128];
};

} //namespace mc
