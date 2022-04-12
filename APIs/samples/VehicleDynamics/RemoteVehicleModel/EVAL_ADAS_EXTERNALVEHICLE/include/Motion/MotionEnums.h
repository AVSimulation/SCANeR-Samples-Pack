
#pragma once

namespace mc {

//MotionCommand is the command sent to the motion platform
enum MotionCommand
{
	commandSettle = 1, //go to a settled position and optionaly, power off. No simulation is running
	commandNeutral = 2, //the simulation is about to start, power on and gradualy move to the 0 positon, do not respond to the vehicle's movement or direct positional command
	commandEngage = 3 //the simulation is running, the platform must move according to the cuing
};

//MotionState describes the current state of the motion platform
//
enum MotionState
{
MCUndefined=0,
MCSettled=1, //the platform is currently settled (usualy rested on a low position, or even powered off), this is the state the platform should be in when the command is "commandSettle"
MCNeutral=2, //the platform is powered on and raised to the 0 position, not moving but ready to start the simulation instantly, this is the state the platform should be in when the command is "commandNeutral"
MCEngaged=3, //the platform is live, responding the direct positional control and virtual vehicle movement
MCBetween=4, //the platform is between one of the 3 previous states
MCFailing=5, //an error has occured on the platform
MCDisconnected=6 //the network or SHM connection to the platform is not responding
};

enum MotionSpecialEffect
{
	CUSTOM_BUMP = 0,		// Motion strategy customizable bump (waveform)
	PREDEFINED_BUMP1,		// Motion platform predefined bump #1
	PREDEFINED_BUMP2,		// Motion platform predefined bump #2
	PREDEFINED_BUMP3,		// Motion platform predefined bump #3
	PREDEFINED_BUMP4,		// Motion platform predefined bump #4
	PREDEFINED_BUMP5,		// Motion platform predefined bump #5
	PREDEFINED_ROAD_RUMBLE, // Motion platform predefined road rumble
};

enum VehiclePlayerState {Play, Pause, Seek};


} //namespace mc
