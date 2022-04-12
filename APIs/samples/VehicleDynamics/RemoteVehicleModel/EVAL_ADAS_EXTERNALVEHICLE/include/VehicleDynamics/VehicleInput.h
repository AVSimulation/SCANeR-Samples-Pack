#pragma once

#include "DriverOutput.h"
#include "WheelState.h"
#include <memory.h>

//all the inputs to the vehicle dynamics model
//these include the environment (weather) as well as the driver output

namespace cats
{
namespace model
{

struct Wheather
{
	Wheather() :
		rain(0),
		snow(0),
		windHeading(0),
		windVelocity(0),
		temperature(20)
	{}

	double  rain;				// Intensity between 0 and 1
	double	snow;				// Intensity between 0 and 1
	double	windHeading;		// in rad. 0 is X (east)
	double	windVelocity;		// In m/s
	double	temperature;		// In degree Celsius
};

struct CorrectivePedals
{
	CorrectivePedals()
	{
		reset();
	}

	void reset()
	{
		accelAdditive = 0;
		accelMultiplicative = 1;
		brakeAdditive = 0;
		brakeMultiplicative = 1;
		clutchAdditive = 0;
		clutchMultiplicative = 1;
		handBrakeAdditive = 0;
		handBrakeMultiplicative = 1;
		timeOfUpdate = 0;
	}

	double	accelAdditive;
	double	accelMultiplicative;
	double	brakeAdditive;
	double	brakeMultiplicative;
	double	clutchAdditive;
	double	clutchMultiplicative;
	double	handBrakeAdditive;
	double	handBrakeMultiplicative; 

	double timeOfUpdate;
};

struct CorrectiveAutonomousPedals : public CorrectivePedals
{

};

struct CorrectiveGearbox : public OutputGearbox
{
	CorrectiveGearbox() :
		isTakeOver(false) {}

	bool				isTakeOver;
};

struct CorrectiveAutonomousGearbox : public CorrectiveGearbox
{

};

struct CorrectiveSteering
{
	CorrectiveSteering()
	{
		reset();
	}

	void reset()
	{
		additiveSteeringWheelAngle = 0;	
		multiplicativeSteeringWheelAngle = 1;	
		additiveSteeringWheelSpeed = 0;	
		multiplicativeSteeringWheelSpeed = 1;	
		additiveSteeringWheelAccel = 0;	
		multiplicativeSteeringWheelAccel = 1;	
		additiveSteeringWheelTorque = 0;
		multiplicativeSteeringWheelTorque = 1;
		timeOfUpdate = 0;
	}

	double	additiveSteeringWheelAngle;	
	double	multiplicativeSteeringWheelAngle;	
	double	additiveSteeringWheelSpeed;	
	double	multiplicativeSteeringWheelSpeed;	
	double	additiveSteeringWheelAccel;	
	double	multiplicativeSteeringWheelAccel;	
	double	additiveSteeringWheelTorque;
	double	multiplicativeSteeringWheelTorque;

	double timeOfUpdate;
};

struct CorrectiveAutonomousSteering : public CorrectiveSteering
{

};

struct CorrectiveLevers : public OutputLevers
{
	CorrectiveLevers() :
		isTakeOver(false) {}

	bool			isTakeOver;
};

struct CorrectiveAutonomousLevers : public CorrectiveLevers
{

};

struct CorrectiveIgnitionKey : public OutputIgnitionKey
{
	CorrectiveIgnitionKey() :
		isTakeOver(false) {}

	bool			isTakeOver;
};

struct CorrectiveAutonomousIgnitionKey : public  CorrectiveIgnitionKey
{

};

struct CorrectiveCommands
{
	CorrectiveCommands()
	{
		reset();
	}

	void reset()
	{
		myAutonomousPedals.reset();
		myPedals.reset();
		myAutonomousGearbox = cats::model::CorrectiveAutonomousGearbox();
		myGearbox = cats::model::CorrectiveGearbox();
		myAutonomousSteering.reset();
		mySteering.reset();
		myAutonomousLevers = cats::model::CorrectiveAutonomousLevers();
		myLevers = cats::model::CorrectiveLevers();
		myAutonomousIgnitionKey = cats::model::CorrectiveAutonomousIgnitionKey();
		myIgnitionKey = cats::model::CorrectiveIgnitionKey();
	}

	CorrectiveAutonomousPedals		myAutonomousPedals;
	CorrectivePedals				myPedals;
	CorrectiveAutonomousGearbox		myAutonomousGearbox;
	CorrectiveGearbox				myGearbox;
	CorrectiveAutonomousSteering	myAutonomousSteering;
	CorrectiveSteering				mySteering;
	CorrectiveAutonomousLevers		myAutonomousLevers;
	CorrectiveLevers				myLevers;
	CorrectiveAutonomousIgnitionKey	myAutonomousIgnitionKey;
	CorrectiveIgnitionKey			myIgnitionKey;
};

//! Defects set scenario. Defects is for one vehicle
struct Defects	
{
	enum VehicleDefectEnum 
	{
		VHLDEFECT_ENGINE_TORQUE = 0,
		VHLDEFECT_INVARIANT_CONVERTER,
		VHLDEFECT_STEERING_TORQUE_ASSISTANCE,
		VHLDEFECT_NB //number of elements of enum
	}; 

	enum WheelDefectEnum 
	{
		WHLDEFECT_TIRE_STIFFNESS=0,
		WHLDEFECT_TIRE_PRESSURE,
		WHLDEFECT_TIRE_GRIP_LONGITUDINAL, 
		WHLDEFECT_TIRE_GRIP_LATERAL,
		WHLDEFECT_WHEEL_DAMPER_COMP,
		WHLDEFECT_WHEEL_DAMPER_REBOUND,
		WHLDEFECT_WHEEL_BUMP_COMP,
		WHLDEFECT_WHEEL_BUMP_REBOUND,
		WHLDEFECT_WHEEL_ELASTICITY_FORCE,
		WHLDEFECT_BRAKE_TORQUE,
		WHLDEFECT_BRAKE_PRESSURE,
		WHLDEFECT_ROLL_DAMPER_COMP,
		WHLDEFECT_ROLL_DAMPER_REBOUND,
		WHLDEFECT_ROLL_BUMP_COMP,
		WHLDEFECT_ROLL_BUMP_REBOUND,
		WHLDEFECT_ROLL_ELASTICITY_FORCE,
		WHLDEFECT_NB //number of elements of enum
	}; 

	Defects()
	{
		for (int i=0;i<VHLDEFECT_NB;i++)
			vehicleDefects[i] = 1.0;

		for (int i=0;i<WHLDEFECT_NB;i++)
			for (int j=0;j<NB_AXLES_MAX;j++) 
				for (int k=0;k<2;k++)
					for (int l=0;l<2;l++)
						wheelDefects[i][j][k][l] = 1.0;
	}

	float vehicleDefects[VHLDEFECT_NB];  //!> defects assigned to the whole vehicle, value: ratio between 0.0 and 1.0
	float wheelDefects[WHLDEFECT_NB][NB_AXLES_MAX][2][2];  //!> defects to an axle, side(left/right), twin(0,1), value: ratio between 0.0 and 1.0
};


struct VehicleInput
{
	VehicleInput()
	{
		myCorrectiveCommands.reset();
	}

	DriverCommands		myDriverCommands;

	Wheather			myWheather;

	//! Commands correction values
	CorrectiveCommands myCorrectiveCommands;
};



} // namespace cats
} // namespace model
