#pragma once

#include "stk/Vector3.h"

#include <memory.h>

//the driver output is divided into several parts, corresponding to different aspects of the driving:
//pedals, steering, gearbox etc.
//these are output from the driver and input into the vehicle dynamics model

#include "VehicleDynamics/Limits.h"
#include "VehicleDynamics/t_Wipers.h"
#include "VehicleDynamics/t_CruiseControlMode.h"
#include "VehicleDynamics/t_GearBoxAutoMode.h"
#include "VehicleDynamics/t_IgnitionKeyPosition.h"
#include "VehicleDynamics/t_Indicators.h"
#include "VehicleDynamics/t_Lights.h"
#include "VehicleDynamics/t_LockDiffMode.h"
#include "VehicleDynamics/t_PlowMode.h"
#include "VehicleDynamics/t_TransferChoice.h"
#include "VehicleDynamics/t_TurretPointing.h"

namespace cats
{
	namespace model
	{

#ifndef __arm__
#pragma pack(push,1)
#endif

		// ENUM definitions
		typedef unsigned int Sirens; // Bits field
		typedef unsigned int AuxiliaryLights; // Bits field

		// OUTPUT structs definitions

		// Steering
		struct OutputSteering
		{
			OutputSteering() :
				isTorqCommand(false),
				pilotSteeringTorq(0.0),
				targetSteeringTorq(0.0),
				effectiveSteeringTorq(0.0),
				steeringWheelAngle(0.0),
				steeringWheelSpeed(0.0),
				steeringWheelAcc(0.0),
				distanceOnTraj(0.0),
				currentTrajError(0.0),
				nearestTrajCurvature(0.0),
				nearestPosOnTraj(0.0,0.0,0.0),
				nearestTrajDirection(0.0,0.0,0.0),
				extrapolatedPosition(0.0,0.0,0.0),
				timeOfUpdate(0) {}

			bool	isTorqCommand; //the vehicle is driver in torq command, otherwise by angle
			double	pilotSteeringTorq; //torque applied by the driver on the steering wheel (N.m) positive to the left
			double	targetSteeringTorq; //torque applied to the steering wheel actuator including special effects (N.m) positive to the left
			double	effectiveSteeringTorq; //torque effectivly applied by the force feedback actuator (N.m) positive to the left

			double	steeringWheelAngle; //(rad), positive to the left
			double	steeringWheelSpeed; //(rad.s-1), positive to the left
			double	steeringWheelAcc; //(rad.s-2), positive to the left

			// filled if driver follows a trajectory
			double distanceOnTraj;			//(m) curvilinear abscissa from the beginning of the traj
			double currentTrajError;		//(m) distance between vehicule and nearest point on traj
			double nearestTrajCurvature;	//(m) curvature at nearest point on traj
			stk::Vector3 nearestPosOnTraj;	//(m) nearest point on traj
			stk::Vector3 nearestTrajDirection;	// direction at nearest point on traj
			stk::Vector3 extrapolatedPosition;	//(m) future position predicted by the pilot

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Pedals
		struct OutputPedals
		{
			OutputPedals() :
				accel(0),
				brake(0),
				handBrake(0),
				clutch(0),
				timeOfUpdate(0) {}
			double	accel;			// [0.0 1.0], 0 is depressed
			double	brake;			// Force (N)
			double	handBrake;		// Force (N)
			double	clutch;			// [0.0 1.0], 0 is depressed

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Extended brake commands for trucks
		struct OutputBrakeSup
		{
			OutputBrakeSup() : 
				isEngineRetarder(false),
				brakeRetarderNotch(0),
				trailerBrakeCommand(0),
				timeOfUpdate(0) {}

			bool isEngineRetarder;		// fowa, Off or On
			double brakeRetarderNotch;	// telma notch, can be 0, 1, .. 4, or intermediate values
			double trailerBrakeCommand;	// percentage of trailer brake command, between 0 and 1

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};	

		// Gearbox
		struct OutputGearbox
		{
			OutputGearbox() : 
				autoMode(TAutoModeDrive),
				wantedGear(0),
				shiftUp(false),
				shiftDown(false),
				isRatioLimit(false),
				minRatio(-2),
				maxRatio(16),
				timeOfUpdate(0) {}

			t_GearBoxAutoMode	autoMode;	
			int	wantedGear;	// only used if (autoMode == TAutoModeManual)
			bool shiftUp;	// only used if (autoMode == TAutoModeSequential)
			bool shiftDown;	// only used if (autoMode == TAutoModeSequential)
			bool isRatioLimit;
			int minRatio;
			int maxRatio;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Additionnal gearbox commands
		struct OutputGearboxSup
		{
			OutputGearboxSup() : 
				transferChoice(TTransferLong),
				lockDiffMode(TLockDiffNone),
				forceLockup(false),
				timeOfUpdate(0) {}

			t_TransferChoice	transferChoice;
			t_LockDiffMode		lockDiffMode;
			bool				forceLockup;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Electronic assistance
		struct OutputElectronicAssistance
		{
			OutputElectronicAssistance() :
				enableABS(true),
				enableTractionControl(true),
				enableESP(true),
				timeOfUpdate(0) {}

			bool enableABS;				
			bool enableTractionControl;	
			bool enableESP;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Ignition key
		struct OutputIgnitionKey
		{
			OutputIgnitionKey() :
				keyPosition(TKeyRun),
				timeOfUpdate(0) {}

			t_IgnitionKeyPosition keyPosition;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};
	
		// Turret
		struct OutputTurret
		{
			OutputTurret():
				nbShots(0),
                shotRythm(0.0),
                turretPointing(TFixeVsVhcPointing),
                aimAngTurret(0.0),
				aimAngGun(0.0),
				targetPosition(0.0,0.0,0.0),
				turretSpeed(0.0),
				gunSpeed(0.0),
				timeOfUpdate(0.0) {}

			int nbShots; // Nombre de tirs à effectuer à partir de l'instant t
            double shotRythm; // Cadence de tir (obligatoirement inférieure à la cadence max de l'arme)
            t_TurretPointing turretPointing; // Type de pointage appliqué à la tourelle
            double aimAngTurret; // Pointage angulaire de l'arme en gisement
			double aimAngGun; // Pointage angulaire de l'arme en site
			stk::Vector3 targetPosition; // Position de la cible par rapport au sol
			double	turretSpeed;
			double	gunSpeed;
			double timeOfUpdate;
		};

		// Demining plow
		struct OutputPlow
		{
			OutputPlow() :
				plowMode(TPlowModeStandby),
				timeOfUpdate(0) {}

			t_PlowMode	plowMode;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// Other commands with no impact on dynamic model
		struct OutputLevers
		{
			OutputLevers() : 
				indicators(INDICATORS_OFF), 
				lights(LIGHTS_OFF), 
				rearWiper(WIPERS_OFF),
				frontWiper(WIPERS_OFF),
				horn(false),
				sirens (0),
				auxiliaryLights (0),
				warnings(false),
				frontFogLights(false),
				rearFogLights(false),
				timeOfUpdate(0) {}

			t_Indicators		indicators;		
			t_Lights			lights;
			t_Wipers			rearWiper;
			t_Wipers			frontWiper;
			bool			horn;
			Sirens			sirens;
			AuxiliaryLights	auxiliaryLights;
			bool			warnings;		
			bool			frontFogLights;
			bool			rearFogLights;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// switches for cruise control and speed limiter
		struct OutputCruiseControl
		{
			OutputCruiseControl() :
				mode(TCruiseOff),
				target(0),
                timeOfUpdate(0) {}

			t_CruiseControlMode	mode;
			double				target; //target speed or acceleration

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		// commands for suspension
		struct OutputSuspensionHeight
		{
			OutputSuspensionHeight() :
				timeOfUpdate(0) 
			{
				for (int i=0;i<NB_AXLES_MAX; i++)
					for (int j=0; j<2; j++)
					{
						EnableRegulation[i][j] = false;
						SuspensionOffset[i][j] = 0;
					}
            }

			bool	EnableRegulation[NB_AXLES_MAX][2];	//True to activate the suspension regulation, false to lock actual the setting
			double	SuspensionOffset[NB_AXLES_MAX][2];	//Positive value to raise the vehicule's body

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		struct OutputClientData
		{
			// cppcheck-suppress memsetClassFloat
			OutputClientData() {memset(this,0,sizeof(OutputClientData));}
			bool isCustomInputOverride[NB_CUSTOM_INTPUT_MAX];
			double overrideCustomInputValues[NB_CUSTOM_INTPUT_MAX];

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		struct OutputAutonomousControls
		{
			// cppcheck-suppress memsetClassFloat
			OutputAutonomousControls()  { memset(this, 0, sizeof(OutputAutonomousControls)); }
			bool isAutonomousModeRequest;
			bool isManualModeRequest;

			double timeOfUpdate; //(s) Time when the value in this struct was written
		};

		struct DriverCommands
		{
			OutputSteering				mySteering;
			OutputPedals				myPedals;
			OutputBrakeSup				myBrakeSup;
			OutputGearbox				myGearbox;
			OutputGearboxSup			myGearboxSup;
			OutputElectronicAssistance	myElectronicAssistance;
			OutputIgnitionKey			myIgnitionKey;
			OutputLevers				myLevers;
			OutputCruiseControl			myCruiseControl;
			OutputTurret				myTurrets[NB_TURRETS_MAX];
			OutputPlow					myPlow;
			OutputSuspensionHeight		mySuspensionHeight;
			OutputClientData			myClientData;
			OutputAutonomousControls	myAutonomousControls;
		};

#ifndef __arm__
#pragma pack(pop)
#endif

	}
}
