
#pragma once

#define PROTOCOL_VERSION 1000 // First version using doubles (Ack message is bigger than MTU of 1500 Bytes)
#define PROTOCOL_VERSION_V2 2000 // Optimized version using floats (Ack message is smaller than MTU of 1500 Bytes and avoid packet fragmentation => Better realtime, Mandatory for some RT systems)

typedef struct
{
	double x, y, z;
} cVector3;

typedef struct
{
	float x, y, z;
} cVector3f;

typedef struct
{
	double x, y, z, roll, pitch, heading;
} cMark;

typedef struct
{
	float x, y, z, roll, pitch, heading;
} cMarkf;

#define MOTION_CMD 5001
typedef struct
{
	int packetID;
	int protocolVersion;
	int command;//motion platform command mc::MotionCommand
	int reserved;
	cMark modulatedVehicleAcceleration;		// longitudinal, lateral and vertical accelerations in [m/s²], heading, pitch and roll accelerations in [rad/s²]
	cMark modulatedVehicleSpeed;		// longitudinal, lateral and vertical speeds in [m/s], heading, pitch, roll speeds in [rad/s]
	cMark modulatedVehiclePosition;	// longitudinal, lateral and vertical positions in [m/s²], heading, pitch, roll positions in [rad]

	//direct command of the platform
	cMark directPosition;    // direct position
	cVector3 directLinearPosition;		// set the predictive position on XY table in [m]
	cVector3 directLinearSpeed;		// set the predictive speed on XY table in [m]
	cVector3 directLinearAcceleration; // set the predictive acceleration on XY table in [m]

	double directRollActuatorPosition;
	double directPitchActuatorPosition;
	double directHeadingActuatorPosition;

	// user Data
	double customData[128];
} MotionCmdPk;

#define MOTION_CMD_V2 5021
typedef struct
{
	int packetID;
	int protocolVersion;
	int command;//motion platform command mc::MotionCommand
	int reserved;
	cMarkf modulatedVehicleAcceleration;		// longitudinal, lateral and vertical accelerations in [m/s²], heading, pitch and roll accelerations in [rad/s²]
	cMarkf modulatedVehicleSpeed;		// longitudinal, lateral and vertical speeds in [m/s], heading, pitch, roll speeds in [rad/s]
	cMark modulatedVehiclePosition;	// longitudinal, lateral and vertical positions in [m/s²], heading, pitch, roll positions in [rad]

	//direct command of the platform
	cMarkf directPosition;    // direct position
	cVector3f directLinearPosition;		// set the predictive position on XY table in [m]
	cVector3f directLinearSpeed;		// set the predictive speed on XY table in [m]
	cVector3f directLinearAcceleration; // set the predictive acceleration on XY table in [m]

	float directRollActuatorPosition;
	float directPitchActuatorPosition;
	float directHeadingActuatorPosition;

	// user Data
	float customData[128];
} MotionCmdPkV2;

#define MOTION_ACK  5002
typedef struct
{
	int packetID;
	int protocolVersion;
	int errorCode;
	int state;	 //mc::MotionState
	char errorMsg[256];
	double platformFrequency; //Control Platform Frequency (Hz)

	cMark effectivePosition;	// hexapod feedback position in DoF
	cMark effectiveSpeed; // hexapod feedback speed in DoF
	cMark effectiveAcceleration; // hexapod feedback acceleration in DoF

	cVector3 effectiveLinearActuatorPos; // X-Y-Z table position
	cVector3 effectiveLinearActuatorSpeed; // X-Y-Z table velocity
	cVector3 effectiveLinearActuatorAcceleration; // X-Y-Z table acceleration

	double effectiveRollActuatorPosition;
	double effectiveRollActuatorSpeed;
	double effectiveRollActuatorAcceleration;

	double effectivePitchActuatorPosition;
	double effectivePitchActuatorSpeed;
	double effectivePitchActuatorAcceleration;

	double effectiveYawActuatorPosition;
	double effectiveYawActuatorSpeed;
	double effectiveYawActuatorAcceleration;

	cMark targetPosition;  // 6DoF motion setpoint
	cVector3 targetLinearActuatorPosition; // X-Y-X table setpoints
	double targetRollActuatorPosition;
	double targetPitchActuatorPosition;
	double targetHeadingActuatorPosition;

	double hexapodActuatorPosition[6]; // motion actual actuator positions 1,..6

	cMark sensorSpeed;
	cMark sensorAcc;

	double customData[128];
} MotionAckPk;

#define MOTION_ACK_V2  5022
typedef struct
{
	int packetID;
	int protocolVersion;
	int errorCode;
	int state;	 //mc::MotionState
	char errorMsg[256];
	float platformFrequency; //Control Platform Frequency (Hz)

	cMarkf effectivePosition;	// hexapod feedback position in DoF
	cMarkf effectiveSpeed; // hexapod feedback speed in DoF
	cMarkf effectiveAcceleration; // hexapod feedback acceleration in DoF

	cVector3f effectiveLinearActuatorPos; // X-Y-Z table position
	cVector3f effectiveLinearActuatorSpeed; // X-Y-Z table velocity
	cVector3f effectiveLinearActuatorAcceleration; // X-Y-Z table acceleration

	float effectiveRollActuatorPosition;
	float effectiveRollActuatorSpeed;
	float effectiveRollActuatorAcceleration;

	float effectivePitchActuatorPosition;
	float effectivePitchActuatorSpeed;
	float effectivePitchActuatorAcceleration;

	float effectiveYawActuatorPosition;
	float effectiveYawActuatorSpeed;
	float effectiveYawActuatorAcceleration;

	cMarkf targetPosition;  // 6DoF motion setpoint
	cVector3f targetLinearActuatorPosition; // X-Y-X table setpoints
	float targetRollActuatorPosition;
	float targetPitchActuatorPosition;
	float targetHeadingActuatorPosition;

	float hexapodActuatorPosition[6]; // motion actual actuator positions 1,..6

	cMarkf sensorSpeed;
	cMarkf sensorAcc;

	float customData[128];
} MotionAckPkV2;


