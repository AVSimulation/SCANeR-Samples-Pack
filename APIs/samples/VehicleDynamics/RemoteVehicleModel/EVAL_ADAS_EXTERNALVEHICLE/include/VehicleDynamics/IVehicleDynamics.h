#pragma once


#include "VehicleInput.h"
#include "VehicleOutput.h"

#include <stdio.h>
#include <stk/Mark.h>
#include <stk/Torser.h>

//predeclarations
namespace cfg {
class Section;
class Vehicle;
}

class IRoadQuery;

namespace cats
{
namespace model
{

struct SimulationData
{
	SimulationData() : rq(NULL), scenario(NULL), nbVehicles(0) 
	{ 
		for(size_t i = 0; i <5; i++)
		{
			vehicles[i] = 0;
			completeModelPath[i][0] = 0;
		}
	}

	//! scenario
	cfg::Section* scenario;

	int nbVehicles;

	//! "Vehicle" section containing instanciation information for each vehicle of the vehicle group
	const cfg::Vehicle* vehicles[5];

	//! complete path of the vehicle model file for each vehicle of the vehicle group
	char completeModelPath[5][256];

	//! rq is an interface on a Road Query plugin.
	//! needs eWantsRoadQuery flags to be valid
	IRoadQuery* rq;
};

struct InitialData
{
	InitialData() :
		initialPosition(0,0,0),
		initialHeading(0), 
		initialSpeed(0)
	{
	}

	/*! initialPosition in global (earth based) frame:
		this is the absolute position that will match to the architect frame position of the vehicle
	*/
	stk::Vector3 initialPosition; 

	/*!	initialHeading (unit=rad) of the vehicle. 
		heading equals 0 if the front of the vehicle is oriented toward X axis of the global frame
	*/
	double initialHeading; 

	//!	initialSpeed (unit=m/s) is given at the center of gravity of the vehicle body
	double initialSpeed;
};

struct WheelInfo
{
	WheelInfo() : tireWidth(0.0), tireAspectRatio(0.0), rimDiameter(0.0) {}
	double getRadius() {return (tireWidth*tireAspectRatio) + (rimDiameter / 2.0); }
	double tireWidth;
	double tireAspectRatio;
	double rimDiameter;
};

enum EEngineType
{
	eNone,
	eDiesel,
	eGas,
	eElectric,
	eHybridDiesel,
	eHybridGas
};

struct VehicleInfo
{
	VehicleInfo()
	{
		memset(this, 0, sizeof(VehicleInfo));
	}

	int getNbWheels() const
	{
		int nbWheels = 0;
		for (int i=0 ; i<myNbAxles ; i++)
			nbWheels += nbWheelsPerAxle[i];
		return nbWheels;
	}
	
	int myNbAxles;
	//! Wheelbase between the first and the last axle.
	/*! in meter
	*/
	double myWheelBase;
	
	//! Ride height at the first axle
	/*! in meter
	*/
	double myRideHeight;

	//! overall dimensions of the vehicle body
	double bodyLength;
	double bodyWidth;
	double bodyHeight;

	//! in rad
	double mySteeringWheelMaxAngle;

	//! in rad
	double myWheelMaxAngle;

	//! in N
	double myBrakePedalMaxForce;

	//! vehicle with torque converter
	bool isWithTorqueConverter;

	//! vehicle with tracks
	bool isWithTracks;

	//! Top speed m/s
	double maxSpeed;

	stk::Vector3 frontArtic; //front articulation point in SCANeR referential
	stk::Vector3 rearArtic; //rear articulation point in SCANeR referential

	int nbElectricMotors;
	int nbWheelsPerAxle[NB_AXLES_MAX]; //current valid values are 1 or 2
	WheelInfo wheel[NB_WHEELS_MAX];

	EEngineType engineType;
	double fuelDensity;
	double engineSpeedIdle;
	double engineSpeedMax;
	int nbGears;
	double gearRatios[NB_GEARS_MAX];
	double emptyMass;

	bool isWithSkidSteering;
};

typedef int EVehicleDynFlags;

const EVehicleDynFlags eNoFeatures					= 0x00000000;
const EVehicleDynFlags eSteeringWheelTorque			= 0x00000001;
const EVehicleDynFlags eCanModifyLights				= 0x00000002;
const EVehicleDynFlags eCanModifyIndicators			= 0x00000004;
const EVehicleDynFlags eSupportsAutoGearboxCommand	= 0x00000008;
const EVehicleDynFlags eSupportsManualCommand		= 0x00000010;
const EVehicleDynFlags eSupportsSequentialCommand	= 0x00000020;
const EVehicleDynFlags eNeedsClutchDuringGearchange = 0x00000040;
const EVehicleDynFlags eSupportsCruiseControl		= 0x00000080;
const EVehicleDynFlags eLsrSlipAngleOpt				= 0x00000100;
const EVehicleDynFlags eAllFeatures					= 0x000001ff;


enum EModelErrorCode
{
	eModelNoError,
	eModelWarning,
	eModelInitError,
	eModelComputationStop,
	eModelUnknownError,
	eModelOutOfRoad
};


const double MAX_BRAKING_PEDAL_FORCE = 400; //400N = 40DaN

class IVehicleDynamicsState
{
public:
	virtual ~IVehicleDynamicsState() {}
};

//! This abstract base class defines the common interface of all vehicle dynamic models.
/*! A plugin should implement all its methods and export the creation fonction from the dll:
	IVehicleDynamics* createVehicleDynamics()
*/
class IVehicleDynamics
{
public:
	//! Destructor must be implemented in daughter classes
	/*! close record file, free memory, ... must be placed in this destructor
	*/
	virtual ~IVehicleDynamics() {}

	//! Gives some information on a specific dynamic model
	/*! This method is called before any other methods. It tells SCANeR what are the needs 
		and capabilities of the dynamic model.
	*/
	virtual EVehicleDynFlags getDynFlags() = 0;

	//!Get the extension of the vehicle model file
	virtual const char* getExtension() = 0;
	

	//! Load simulation data (scenario, vehicle...)
	virtual bool loadModel(	const SimulationData& data ) = 0;

	//! Return error message.
	/*! This method is called each time 'false' was returned on one of the other methods.
	The string is then displayed in the SCANeR console as an Error message.
	errorCode: not used yet.
	*/
	virtual const char* getError(EModelErrorCode& errorCode) = 0;


	//! Return some vehicle information needed by the module to communicate properly with SCANeR
	virtual bool getVehicleInfo(int vehicleIndex, VehicleInfo& info) = 0;

	//! Initialisation or re-initialisation of the model
	/*! During this function, the model should (re)initialize all data, for example by placing the vehicle
		at the exact position on the road, stetting right speed, ...
		a statico dynamic initialization can be done.
	*/
	virtual bool initModel(const InitialData& initialData, double curTime) = 0;

	//! Set the new input data
	virtual bool setInput(const VehicleInput& input) = 0;

	//! Set defects on the vehicle
	virtual bool setDefects(int vehicleIndex, const Defects& defects) = 0;
	

	//! During this function, the model should perform one step of simulation.
	/*! deltaTime: time elapsed between 2 steps.
	*/
	virtual bool stepModel(double deltaTime) = 0;

	//! Get the current output data
	/*! When a vehicle is composed of several parts (like a truck and its trailer), the result is given per part. 
	*/
	virtual bool getOutput(int vehicleIndex, VehicleOutput& output) = 0;

	//! Save and restore current state
	virtual IVehicleDynamicsState* backupCurrentState() {return NULL;}
	virtual bool restoreState(IVehicleDynamicsState* state) {return false;}


	//! Apply external force to the model
	/*! The external torser (applicationPoint, force, momentum) is defined in CoG frame
	*/
	virtual void applyForce(int vehicleIndex, const stk::Torser& externalForce) {};

	//!Set the speed of the vehicle
	virtual bool setSpeed(double speedObligatory) { return true; }

	virtual void setLogFolder(const char* logFolder) {}

	//! these methods are called when the SCANeR simulation recieves a command Start/Go/Pause/Stop
	virtual void onStart() {}
	virtual void onGo() {}
	virtual void onPause() {}
	virtual void onStop() {}

	//! Called at all times turing the simulation so the model can do continuous tasks such as maintain communication with a remote host
	virtual void onIdle() {}



};

} // namespace cats
} // namespace model

typedef cats::model::IVehicleDynamics* (*FCT_createVehicleDynamics)();


