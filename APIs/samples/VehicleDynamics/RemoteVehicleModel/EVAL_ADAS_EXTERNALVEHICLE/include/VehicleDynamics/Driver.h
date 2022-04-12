#pragma once

#include <string>
#include "stk/Vector3.h"
#include "VehicleDynamics/IVehicleDynamics.h"
#include "VehicleDynamics/VehicleOutput.h"

struct EGComplet;

namespace cfg {
class Section;
class Vehicle;
}

namespace ITN
{
	class Network;
}

namespace cats
{
namespace driver
{
enum EDriverErrorCode
{
	eDriverNoError,
	eDriverWarning,
	eDriverUnknownError,
	eDriverInitError,
	eDriverEndOfTrajectory
};

enum DriverType // type of driver
{
	NO_DRIVER		= 0x000,
	TRAFFIC_DRIVER	= 0x001,
	VIRTUAL_DRIVER	= 0x002,
	HUMAN_DRIVER	= 0x003,
	MIXED_DRIVER	= 0x004,
	REVERSE_DRIVER	= 0x005,
	EXTERNAL_DRIVER = 0xfff	//driver type not defined in SCANeR
};

static const char* toText(DriverType type)
{
	switch (type)
	{
	case NO_DRIVER: return "NO_DRIVER";
	case TRAFFIC_DRIVER: return "TRAFFIC_DRIVER";
	case VIRTUAL_DRIVER: return "TRAFFIC_DRIVER";
	case HUMAN_DRIVER: return "TRAFFIC_DRIVER";
	case MIXED_DRIVER: return "TRAFFIC_DRIVER";
	case EXTERNAL_DRIVER: return "EXTERNAL_DRIVER";
	case REVERSE_DRIVER: return "REVERSE_DRIVER";
	}
	return "";
}

static DriverType toDriverType(const std::string& text)
{
	if (text == "TRAFFIC_DRIVER" || text == "TrafficDriver")
		return TRAFFIC_DRIVER;
	if (text == "VIRTUAL_DRIVER" || text == "VirtualDriver")
		return VIRTUAL_DRIVER;
	if (text == "HUMAN_DRIVER" || text == "HumanDriver")
		return HUMAN_DRIVER;
	if (text == "MIXED_DRIVER" || text == "MixedDriver")
		return MIXED_DRIVER;
	if (text == "EXTERNAL_DRIVER" || text == "ExternalDriver")
		return EXTERNAL_DRIVER;
	if (text == "REVERSE_DRIVER" || text == "ReverseDriver")
		return REVERSE_DRIVER;

	return NO_DRIVER;
}


class IDriverState
{
public:
	virtual ~IDriverState() {}
};

//! This abstract base class defines the common interface of all vehicle dynamic models.
/*! A plugin should implement all its method and the creation fonction :
	IDriver* MakePlugin()
*/
class IDriver
{
public:
	typedef unsigned int OutputFlags;
	enum t_OutputFlags {
		TSteering				= 0x00000001,
		TPedals					= 0x00000002,
		TBrakeSup				= 0x00000004,
		TGearbox				= 0x00000008,
		TGearboxSup				= 0x00000010,
		TElectronicAssistance	= 0x00000020,
		TIgnitionKey			= 0x00000040,
		TLevers					= 0x00000080,
		TCruiseControl			= 0x00000100,
		TTurret0				= 0x00000200,
		TTurret1				= 0x00000400,
		TTurret2				= 0x00000800,
		TTurret3				= 0x00001000,
		TTurret4				= 0x00002000,
		TPlow					= 0x00004000,
		TSuspensionHeight		= 0x00008000,
		TClientData				= 0x00010000,
		TAutonomousControls		= 0x00020000,
		TAll					= 0xffffffff
	};
public:
	virtual ~IDriver() {}
	
	//! Load the sections
	virtual bool load(const cats::model::VehicleInfo& vhcInfo, 
		cfg::Section* driverSection,
		cfg::Vehicle* vehicleSection,
		ITN::Network* network) = 0;

	virtual void reset(double time, double steeringWheelAngle, double accel, double brake, int gear) = 0;

	enum t_SteeringCommand
	{
		TSteeringCentering, //no simulation is running but the acquisition system is alive (enable centering on force feedback)
		TSteeringDisabled, //the scenario is being loaded, the application might be unresponsive, don't do anything dangerous (ff=0)
		TSteeringDynamic //the simulation is running, apply force feedback etc.
	};
	virtual bool setInput(t_SteeringCommand steeringCommand, double time, double deltaT, const cats::model::VehicleOutput& input, const EGComplet* eg) = 0;

	//! Get the current output data
	virtual OutputFlags getOutputFlags() = 0;
	virtual bool getOutput(cats::model::OutputSteering& output) = 0;
	virtual bool getOutput(cats::model::OutputPedals& output) = 0;
	virtual bool getOutput(cats::model::OutputBrakeSup& output) = 0;
	virtual bool getOutput(cats::model::OutputGearbox& output) = 0;
	virtual bool getOutput(cats::model::OutputGearboxSup& output) = 0;
	virtual bool getOutput(cats::model::OutputElectronicAssistance& output) = 0;
	virtual bool getOutput(cats::model::OutputIgnitionKey& output) = 0;
	virtual bool getOutput(cats::model::OutputLevers& output) = 0;
	virtual bool getOutput(cats::model::OutputCruiseControl& output) = 0;
	virtual bool getOutput(cats::model::OutputTurret& output, int i) = 0;
	virtual bool getOutput(cats::model::OutputPlow& output) = 0;
	virtual bool getOutput(cats::model::OutputSuspensionHeight& output) = 0;
	virtual bool getOutput(cats::model::OutputClientData& output) = 0;
	virtual bool getOutput(cats::model::OutputAutonomousControls& output) = 0;
	
	virtual double getDistanceOnTrajectory() = 0;

	//return the driver type
	virtual DriverType getDriverType() = 0;

	//! Return error message.
	/*! This method is called each time 'false' was returned on one of the other methods.
		The string is then displayed in the SCANeR console as an Error message.
	*/
	virtual const char* getError( EDriverErrorCode& errorCode ) = 0;

	virtual IDriverState* backupCurrentState() const {return NULL;}
	virtual bool restoreState(IDriverState* state) {return false;}

};

} // namespace cats
} // namespace driver

typedef cats::driver::IDriver* (*FCT_createDriver)();
