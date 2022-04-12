
#pragma once

#include "VehicleDynamics/Limits.h"
#include "VehicleDynamics/t_TurretPointing.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define MODEL_SYSTEM_PORT 8842

#define PROTOCOL_VERSION 190

#define PACKET_SEND_DELTAT 0.01

//! Simulation states
#define SIM_MODE_INITIALIZE 1
#define SIM_MODE_DYNAMIC 2
#define SIM_MODE_TERMINATE 3

#pragma pack(push,1)

//================================================================================
// Inputs
//================================================================================

//! Wheels Input data
typedef struct
{
	double contactPosition[3];  // Position of contact point X,Y,Z (world frame, meters)
	double contactNormal[3];	// Normal at contact point X,Y,Z
	double grip;				// Grip
	int groundIndex;			// Ground index
	int laneType;				// Type of road lane
} ModelInputWheelPk;
void convertModelInputWheelPk(ModelInputWheelPk* pk, int toNetworkOrder);

//! Vehicle Input data
#define MODEL_INPUT_PK 505
typedef struct
{
//! Control
	int packetNumber;			// Number of the packet
	int packetID;				// Packet identifier
	int protocolVersion;		// Protocol version
	int simulationMode;			// Current simulation mode (SIM_MODE_INITIALIZE, SIM_MODE_DYNAMIC, SIM_MODE_TERMINATE)
//! Initial conditions
	char options[256];			// Free option string
	double initHeading;			// Initial heading (rad)
	double initSpeed;			// Initial speed (m/s)
	double initGroundPos[3];	// Initial world position of measure point
	double initGroundNorm[3];	// Ground normal at initial world position

//! Real time simulation data
	double scANeRTime;			// Current SCANeR simulation time
	char isCommandOverride;		// Option, use SCANeR driver inputs (1), use internal driver inputs (0)
//! SCANeR driver inputs (comming from DriverHandler, if used)
	double steeringWheel;		// Steering wheel angle (rad)
	double steeringWheelSpeed;	// Steering wheel speed (rad/s)
	double accelerator;			// Throttle pedal position [0,1]
	double brake;				// Brake pedal force (N)
	double clutch;				// Clutch pedal position [0,1]
	int wantedGear;				// Wanted gear ratio
	int gearBoxAutoMode;		// Gearbox mode
	char shiftUp;
	char shiftDown;
	int ignitionKey;			// Ignition key position (Off = 0, Accessories = 1, Run = 2, Ignition = 3)
	double parkingBrake;		// Parking brake force (N)
	char fowa;					// fowa (Engine retarder), Off = 0 or On = 1
	double telma;				// telma notch, can be 0, 1, .. 4, or intermediate values
	int indicators;				// Indicator lever position (Right = -1, Off = 0, Left = 1)
	int lights;					// Lights lever position (LIGHTS_OFF = 0, LIGHTS_PARKING = 1, LIGHTS_LOW = 2, LIGHTS_HIGH = 3)
	int rearWiperState;			// Rear wiper lever position (OFF = 0, INTERMITTENT_1 = 1, INTERMITTENT_2 = 2, INTERMITTENT_3 = 3, LOW_SPEED = 4, HIGH_SPEED = 5, AUTOMATIC = 6)
	int frontWiperState;		// Front wiper lever position (OFF = 0, INTERMITTENT_1 = 1, INTERMITTENT_2 = 2, INTERMITTENT_3 = 3, LOW_SPEED = 4, HIGH_SPEED = 5, AUTOMATIC = 6)
	char horn;					// Horn (Off = 0, On = 1)
	char warnings;				// Warning lights  (Off = 0, On = 1)
	char frontFogLights;		// Front fog lights  (Off = 0, On = 1)
	char rearFogLights;			// Rear fog lights  (Off = 0, On = 1)
	double trailerBrake;		// Trailer brake force (N)
	int rVLVState;				// Speed Regulator/Limiter mode
	double rVLVTarget;			// Speed Regulator/Limiter setting
	int transferChoice;					// Sirens states (bitset)
	int lockDiffMode;		// Aux lights states (bitset)
	double customVehicleInput[NB_CUSTOM_INTPUT_MAX];		// Custom Vehicle Inputs
//! Environment data
	double rain;				// Intensity between 0 and 1
	double snow;				// Intensity between 0 and 1
	double windHeading;			// in rad. 0 is X (east)
	double windVelocity;		// In m/s
	double temperature;			// In degree Celsius
	double externalTorserApplicationPoint[3];
	double externalTorserForce[3];
	double externalTorserMoment[3];
	int numberOfContactPoints;	// Number of wheels
} ModelInputPk;
void convertModelInputPk(ModelInputPk* pk, int toNetworkOrder);

//================================================================================
// Outputs
//================================================================================

//! Electric motor Output data
typedef struct
{
	double speed;
	double load;
	double current;
	double reserved[16];
} ModelOutputElectricMotorPk;

//! Wheels Output data
typedef struct
{
	double hubPosition[6];		// Position of wheel hub (wheel center) X,Y,Z (world frame, meters)
	double wheelRotationSpeed;	// Wheel rotation speed (rad/s)
	double wheelAngle;			// Current wheel rotation angle
	double vhlSx;				// 
	double vhlDelta;			//
} ModelOutputWheelPk;
void convertModelOutputWheelPk(ModelOutputWheelPk* pk, int toNetworkOrder);

//! Vehicle Output data
#define MODEL_OUTPUT_PK 506
typedef struct
{
	//! Control
	int packetNumber;			// Number of the packet
	int packetID;				// Packet identifier
	int protocolVersion;		// Protocol version
	int errorCode;				// Last error code (0 if no error)
	char errorMessage[256];		// Last error message
	double vehicleModelSimulationTime;	// Vehicle model simulation time

	//! Vehicle outputs
	double pos[3];					// Position of reference point of the vehicle X,Y,Z (world frame, meters)
	double roll;					// Roll (rad)
	double pitch;					// Pitch (rad)
	double heading;					// Heading (rad)
	double speed[6];				// Vehicle speeds (X,Y,Z)(m/s) (Roll,Pitch,Heading)(rad/s)
	double accel[6];				// Vehicle accelerations (X,Y,Z)(m/s²) (Roll,Pitch,Heading)(rad/s²)
	char engineStatus;				// Engine running flag (0 = OFF, 1 = ON)
	double engineSpeed;				// Engine speed

	// Effective commands (after modulation by model) and vehicle states
	double effectiveSteeringWheelAngle;		// Effective steering wheel angle (rad)
	double SteeringWheelFeedbackTorque;		// Steering wheel torque (N)
	double effectiveGasPedalPos;			// Effective throttle pedal [0,1]
	double effectiveBrake;					// Effective brake pedal force (N)
	double effectiveHandBrake;				// Effective parking brake force (N)
	double effectiveClutch;					// Effective clutch pedal [0,1]
	int gearEngaged;						// Current gear number
	int GearBoxMode;						// Current gearbox mode
	int effectiveIgnitionKeyPosition;		// Effective ignition key (Off = 0, Accessories = 1, Run = 2, Ignition = 3)
	double consumption;						// Current consumption (m3/s)
	char isEngineRetarder;
	double brakeRetarderNotch;
	double trailerBrake;
	int transferChoice;
	int lockDiffMode;
	char forceLockup;
	int plowMode;
	char horn;
	int lights;
	char rearWiperState;					// Rear Wiper state
	char frontWiperState;					// Front Wiper state
	int reserved1;
	int reserved2;
	double batteryStateOfCharge;
	double reserved[128];
	double customVehicleOutput[NB_CUSTOM_OUTPUT_MAX];
	int electricMotorNumber;
	int wheelNumber;
} ModelOutputPk;
void convertModelOutputPk(ModelOutputPk* pk, int toNetworkOrder);

typedef struct
{
	int TypeArchitecture;
	t_TurretPointing TypePointage;
	int NbreTirs; // Nombre de tirs à effectuer à partir de l'instant t
	double PointageAngGisement;  // Cadence de tir (obligatoirement inférieure à la cadence max de l'arme)
	double PointageAngSite; // Type de pointage appliqué à la tourelle 
	double PosCible[3];  // Pointage angulaire de l'arme en gisement
	double CadenceTir; // Pointage angulaire de l'arme en site
	double turretSpeed; 
	double gunSpeed;

} ModelInputTurretPk;

typedef struct
{
	double pos[6]; //position relative to the parent of the articulated part
	double speed[6]; //absolute speed
	double accel[6]; //absolute acceleration
} ModelOutputTurretPk;

#ifdef __cplusplus
}
#endif //__cplusplus

#pragma pack(pop)
