#pragma once

#include "stk/Vector2.h"
#include "stk/Mark.h"

//these are the outputs of the motion communication
//they contain the feedback sent by the motion platform
//most notably, the effective platform position that can lag the commanded position because of electrical and mechanical limitations
//also, this is where the platform error codes are sent by the platform to the rest of the software

struct MotionComOutput
{
	double platformFrequency; //Frequency of the platform control (Hz)

//the current state of the hexapod mesured on the platform
	stk::Mark effectivePosition;	// hexapod feedback position in DoF (m and rad)
	stk::Mark effectiveSpeed; // hexapod feedback speed in DoF (m/s and rad/s)
	stk::Mark effectiveAcceleration; // hexapod feedback acceleration in DoF (m/s² and rad/s²)

//the current state of the X/Y table, mesured on the platform
	stk::Vector3 effectiveLinearActuatorPos; // X-Y(-Z) table position (m)
	stk::Vector3 effectiveLinearActuatorSpeed; // X-Y(-Z) table velocity (m/s)
	stk::Vector3 effectiveLinearActuatorAcceleration; // X-Y(-Z) table acceleration (m/s²)

//most simulators should disregard these values, these are only used for simulators with two actuators for extra roll and pitch angles
	double effectiveRollActuatorPosition;
	double effectiveRollActuatorSpeed;
	double effectiveRollActuatorAcceleration;

	double effectivePitchActuatorPosition;
	double effectivePitchActuatorSpeed;
	double effectivePitchActuatorAcceleration;

//the current state of the Yaw table
	double effectiveYawActuatorPosition; //the current yaw angle of the yaw table (rad) mesured on the platform
	double effectiveYawActuatorSpeed; //the yaw angular speed of the yaw table (rad/s)
	double effectiveYawActuatorAcceleration; //the yaw angular acceleration of the yaw table (rad/s²)

	stk::Mark targetPosition;  //6DoF motion setpoint (m and rad) (the position commanded by the motion cueing)
	stk::Vector3 targetLinearActuatorPosition; // X-Y-X table setpoints (m) (the position commanded by the motion cueing)
	double targetRollActuatorPosition; //(rad)
	double targetPitchActuatorPosition; //(rad)
	double targetHeadingActuatorPosition; //Yaw table target position (rad) (the position commanded by the motion cueing)

	double hexapodActuatorPosition[6]; //hexapod actual actuator positions 1,..6 //(m) these are the hexapod's linear actuator positions (not the same as degrees of freedom X/Y/Z/R/P/H)

//if there is a sensor on the platform to mesure acceleration and speed
	stk::Mark sensorSpeed; //(m/s and rad/s)
	stk::Mark sensorAcc; //(m/s² and rad/s²)

	double customData[128];

	double hexapodActuatorSpeed[6]; // hexapod actual actuator positions 1,..6 //(m)

//the virtual sensors are positioned on the platform in the MotionGeometry.cfg file
//these sensors are not present on the platform, their output is estimated from the platform movement feedback
	stk::Mark virtualSensorPos[5]; //(m and rad)
	stk::Mark virtualSensorSpeed[5]; //(m and rad)
	stk::Mark virtualSensorAcc[5]; //(m and rad)
};
