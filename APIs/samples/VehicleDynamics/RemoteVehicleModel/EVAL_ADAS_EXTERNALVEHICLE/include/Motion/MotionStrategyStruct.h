
#pragma once

#include "stk/Mark.h"
#include "stk/Vector2.h"
#include "stk/Vector3.h"

//These are the output of the motion cueing strategy
//they are then sent as input to the motion communication as command for the platform

struct MotionStrategyOutput
{
//movement of the virtual vehicle
	stk::Mark modulatedVehicleAcceleration;		// longitudinal, lateral and vertical accelerations in [m/s²], heading, pitch and roll accelerations in [rad/s²]
	stk::Mark modulatedVehicleSpeed;		// longitudinal, lateral and vertical speeds in [m/s], heading, pitch, roll speeds in [rad/s]
	stk::Mark modulatedVehiclePosition;	// longitudinal, lateral and vertical positions in [m/s²], heading, pitch, roll positions in [rad]

//direct command of the platform
	stk::Mark directPosition;    // direct position setpoint
	stk::Vector3 directLinearPosition;		// position setpoint on XY table in [m]
	stk::Vector3 directLinearSpeed;
	stk::Vector3 directLinearAcceleration;

	double directRollActuatorPosition;
	double directPitchActuatorPosition;
	double directHeadingActuatorPosition; //position setpoint for the yaw table

	// user Data
	double customData[128];

	// Special effects 
	int specialEffect; // 0 or 1
	double bump[5]; // trigger and amplitude for bump
	double frequency[20]; // frequencies of waveforms
	stk::Vector3 gain[20]; // x axis, y axis, z axis of waveforms
	bool authorizePlay;
	bool authorizePause;
	bool authorizeSeek;
};
