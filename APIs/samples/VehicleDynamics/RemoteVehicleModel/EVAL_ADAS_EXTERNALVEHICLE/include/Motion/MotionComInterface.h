//
// File : motionComInterface.h
// Copyright (C) 2000, AVSimulation all rights reserved

//
// This class is an interface of the communication with a platform


#pragma once

#include "Motion/MotionComStruct.h"
#include "Motion/MotionStrategyStruct.h"
#include "Motion/MotionEnums.h"
#include <string>

// Struc used for Cueing Settings Updates
struct CueingSettings
{
	std::string ftpServer;
	std::string ftpUser;
	std::string remoteFolder;
	std::string cueingFile;
	std::string protocol;
};

// Functionnalities that can be implemented in the plugin
#define MOTION_COM_FEATURE_NONE 0x0000
#define MOTION_COM_FEATURE_CUEING_SETTINGS 0x0001 //the motion com supports sending cuing settings by FTP
#define MOTION_COM_FEATURE_VIBRATION 0x0002 //the motion com supports vibration channels
#define MOTION_COM_FEATURE_XY_TABLE 0x0004 //the motion has an XY table
#define MOTION_COM_FEATURE_FEEDBACK_SPEED 0x0008 //the motion com returns the current motion speed
#define MOTION_COM_FEATURE_FEEDBACK_ACCEL 0x0010 //the motion com returns the current motion acceleration
#define MOTION_COM_FEATURE_RECOVERY_PROCEDURE	0x0020 //the motion com has a recovery procedure
#define MOTION_COM_FEATURE_CUEING 0x0040	//the motion com has a built in cueing algorithm is a feature of the platform
#define MOTION_COM_FEATURE_EXTRA_POS 0x0080 //the motion com supports commanding by position
#define MOTION_COM_FEATURE_FORCE_TIME_STEP 0x0100 //the motion com returns the time step to be used by motion
#define MOTION_COM_FEATURE_FEEDBACK_ACTUATOR_TRAVEL 0x0200 //the motion com returns the travel of each actuator
#define MOTION_COM_FEATURE_FEEDBACK_ACTUATOR_TRAVEL_SPEED 0x0400 //the motion com returns the travel of each actuator

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//						Communication Structure in Motion Module									   //													
/////////////////////////////////////////////////////////////////////////////////////////////////////////

enum MotionRecoveryState
{
	PF_RECOVERY_NONE=0,
	PF_RECOVERY_REQUESTED,
	PF_RECOVERY_IN_PROGRESS,
	PF_RECOVERY_DONE
};

/*------------------------------------------------------------*/
/* classes declared in this header: */

class MotionComInterface
{
public:
	virtual ~MotionComInterface(){};
	
	// Return the extended functions implemented by the plugin (cueing settings etc...)
	virtual int implementedFunctions() const =0;

	// send and receive data with a platform
	virtual bool sendMessage(double deltaT, const MotionStrategyOutput& inp) = 0;
	virtual bool receiveMessage()=0;
	//the motion com must return the current wanted time step for motion, this is only called if the flag MOTION_COM_FEATURE_FORCE_TIME_STEP is set in implementedFunctions()
	virtual double getTimeStep()=0;
	
	// check if motion communication is alive.
	virtual bool motionAlive()=0;
	
	// command Platform
	virtual void goToSettled()=0;
	virtual void goToNeutral()=0;
	virtual void goToEngaged()=0;
	virtual void goToStop()=0;
	virtual void goToOff()=0;

	virtual MotionComOutput getMotionFeedback()=0;
	virtual mc::MotionState getMotionCurrentState()=0;
	virtual void getPlatformSpecificState(int& code, std::string& message)=0;

	// Cueing Settings
	virtual CueingSettings getCueingSettings() = 0;
	virtual CueingSettings reloadCueingSettings() = 0;
	virtual void saveCueingSettings(CueingSettings settings) = 0;

	// This function must restart the target to take into account a cueing parameters modification
	virtual void restartMotionTarget(const char* user, const char* password) = 0;

	// Recovery procedure functions
	// Execute recovery procedure 
	virtual void executeRecoveryProcedure()=0;
	// Is Emergency Stop detected
	virtual bool isEmergencyStop()=0;
	// Recovery Procedure state
	virtual MotionRecoveryState getRecoveryProcedureState()=0;

};

typedef MotionComInterface* (*FCT_createMotionCom)(const char* configFile);

#ifdef WIN32
#define MOTION_PLUGIN_EXPORTS __declspec(dllexport)
#else
#define MOTION_PLUGIN_EXPORTS
#endif
