#pragma once

#include "WheelState.h"
#include "DriverOutput.h"
#include "Motion/ArticulatedPartId.h"

//the complete outputs of a SCANeR vehicle dynamics model
//any SCANeR vehicle from Simple to Callas and including customer vehicle models must output these values

namespace cats
{

//Indices of lights bits :
const int LEFT_INDIC_IND      = 0;
const int RIGHT_INDIC_IND     = 1;
const int STOP_LIGHTS_IND     = 2;
const int DIPPED_LIGHTS_IND   = 3;
const int FULL_LIGHTS_IND     = 4;
const int FOG_LIGHTS_IND      = 5;
const int REVERSE_LIGHTS_IND  = 6;
const int SIDE_LIGHTS_IND     = 7;
const int REAR_FOG_LIGHTS_IND = 8;
const int REAR_LIGHTS_IND	  = 9;
const int LEFT_DRL_IND        = 10;
const int RIGHT_DRL_IND       = 11;

typedef unsigned int EVehicleLights;
const EVehicleLights	eNoLights			= 0x00000000;
const EVehicleLights	eLeftSignal			= 1 << LEFT_INDIC_IND;
const EVehicleLights	eRightSignal		= 1 << RIGHT_INDIC_IND;
const EVehicleLights	eStopLights			= 1 << STOP_LIGHTS_IND;
const EVehicleLights	eDippedLights		= 1 << DIPPED_LIGHTS_IND; // Dipped (GB) or Dimmed (US)
const EVehicleLights	eMainBeam			= 1 << FULL_LIGHTS_IND;
const EVehicleLights	eFrontFog			= 1 << FOG_LIGHTS_IND;
const EVehicleLights	eBackLights			= 1 << REVERSE_LIGHTS_IND;
const EVehicleLights	eSideLights			= 1 << SIDE_LIGHTS_IND;
const EVehicleLights	eRearFog			= 1 << REAR_FOG_LIGHTS_IND;
const EVehicleLights	eRearLights			= 1 << REAR_LIGHTS_IND;
const EVehicleLights	eDrlLeft			= 1 <<  LEFT_DRL_IND;
const EVehicleLights	eDrlRight			= 1 <<  RIGHT_DRL_IND;
const EVehicleLights	eAuxiliaryLights	= 0xF0000000; // Full lights
const EVehicleLights	eAllLights			= 0xFFFFFFFF;

namespace model
{

struct MobileState
{
	stk::Mark	myArchitectPosition;
	stk::Mark	myCOGPosition;
	stk::Mark	myCOGSpeed;
	stk::Mark	myCOGAcceleration;
};

// Degree of freedom
struct DofState
{
	DofState() : myPos(0.0), mySpeed(0.0), myAcceleration(0.0) {}
	double	myPos;
	double	mySpeed;
	double	myAcceleration;
};

struct FireEvent
{
	short id;   // id of the turret architecture
	double force;
	stk::Vector3 position;
};

struct VehicleState
{
	VehicleState() : mySpeedometerSpeed(0.0), traveledDist(0.0), myLights(LIGHTS_OFF), myRearWiper(WIPERS_OFF), myFrontWiper(WIPERS_OFF), myHorn(false), mySirens(0), myAuxiliaryLights(0) {}
	//! Body movement
	/*! Position of the ARCHI frame:
		x (unit=m) The absolute X coordinate of the middle of front axle.
		y (unit=m) The absolute Y coordinate of the middle of front axle.
		z (unit=m) The absolute Z coordinate of the bottom of the body at the middle of front axle.
		r (unit=rad) X rotation: The roll of this vehicle. .
		p (unit=rad) Y rotation: The pitch of this vehicle.
		h (unit=rad) Z rotation: The heading of this vehicle. 

		The X axis is oriented toward the back of the vehicle
		The Y axis is oriented toward the right of the vehicle
		The Z axis is oriented toward the top of the vehicle
		
		Starting from the absolute referential, doing successively 3 rotations according to 'heading', 'pitch' and 'roll' gives the positioning of the vehicle 
		These 3 angles are applied in this order:
		- first the heading (Z)
		- then the pitch (Y)
		- then the roll (X)

		Speed and Acceleration are given at the center of gravity of the body
	*/
	MobileState				myVehicleBody;  // Architect position + COG dynamics of the vehicle frame

	double					mySpeedometerSpeed;		//! as calculated in a vehicle, average of rear wheels speed.

	double					traveledDist; // traveled Distance 

	//! vehicle lights, might come directly from cab or be re-calculated depending on some model data.
	EVehicleLights			myLights;

	//! Wipers state
	t_Wipers					myRearWiper;
	t_Wipers					myFrontWiper;

	//! Horn state
	bool					myHorn;			
	
	/*! Wheels data.
	ordered from front to back and from left to right
	*/
	WheelState				myWheels[NB_WHEELS_MAX];

	Sirens					mySirens;
	
	AuxiliaryLights			myAuxiliaryLights;
};

struct EngineState
{
	EngineState() : myEngineState(false), myConsumption(0), myPollution(0), myEngineSpeed(0)
		 {}

	bool		myEngineState;			//! on or off. While starting it is off
	double		myConsumption;			//! m3/s number indicating instantaneous petrol use
	double		myPollution;			//! kg/s Pollution Kg of CO2 / seconds
	double		myEngineSpeed;			//! engine speed in rad/s
};

struct ElectricMotorState
{
	ElectricMotorState() : mySpeed(0), myLoad(0), myCurrent(0) {}

	double mySpeed;
	double myLoad;
	double myCurrent;
};

struct ArticulatedPartState
{
	ArticulatedPartState() : id(PT_NONE), remainingMunitions(0) {}
	t_ArticulatedPartId id;
	stk::Mark pos; //position relative to the parent of the articulated part
	stk::Mark speed; //absolute speed
	stk::Mark accel; //absolute acceleration

	int  remainingMunitions; // all types of munitions associated to a weapon, 0 for turrets and plows 
	stk::Vector3 shootPosition; // in world frame

	stk::Vector3 force;
};

struct VehicleOutput
{
	VehicleOutput() : mySteeringWheelTorque(0), myEffectiveSteeringWheelAngle(0), myGearEngaged(0),
		GearBoxMode(TAutoModeManual), effectiveIgnitionKeyPosition(TKeyOff), isEngineRetarder(false), brakeRetarderNotch(0),
		trailerBrake(0), transferChoice(TTransferShort), lockDiffMode(TLockDiffNone), forceLockup(false), plowMode(TPlowModeStandby), myBatteryStateOfCharge(0), timeOfUpdate(0)
	{
		memset(customOutputValues, 0, sizeof(customOutputValues));
	}

	VehicleState				myVehiculeState;

	EngineState					myEngineState;

	double myBatteryStateOfCharge;
	ElectricMotorState myElectricMotorState[20];

	ArticulatedPartState		myArticulatedPart[20];

	//! feedback torque to apply on the steering wheel
	/*! This data is used only if the model returns eCanHandleSteeringWheel
		Description:	steering wheel torque to be applied to the steering wheel of the cabin, calculated by the dynamic model or a specific steering wheel dynamic model<br>
		Unit:	in N.m (Newton * meters)*/
	double		mySteeringWheelTorque;

	//! commands effectively applied to the model (after regulations)
	double			myEffectiveSteeringWheelAngle;
	int				myGearEngaged;
	OutputPedals	myEffectivePedals;

	double		customOutputValues[NB_CUSTOM_OUTPUT_MAX];

	t_GearBoxAutoMode GearBoxMode;
	t_IgnitionKeyPosition effectiveIgnitionKeyPosition;
	bool isEngineRetarder;
	double brakeRetarderNotch;
	double trailerBrake;
	t_TransferChoice transferChoice;
	t_LockDiffMode lockDiffMode;
	bool forceLockup;
	t_PlowMode plowMode;

	double timeOfUpdate;
};

} // namespace model
} // namespace cats

