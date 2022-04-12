
//Copyright © A.V. Simulation 1993-2019

//=========================================================================================
//ATTENTION:
//This header file defines the communacation between Callas and external modules
//this file must not be modified or the communication will no longer work as expected
//=========================================================================================

#ifndef _CAL_MODULE_H_
#define _CAL_MODULE_H_

#define OKTAL_VERSION_API 500000

#include "VehicleDynamics/t_CruiseControlMode.h"
#include "VehicleDynamics/t_GearBoxAutoMode.h"
#include "VehicleDynamics/t_IgnitionKeyPosition.h"
#include "VehicleDynamics/t_LockDiffMode.h"
#include "VehicleDynamics/t_PlowMode.h"
#include "VehicleDynamics/t_TransferChoice.h"
#include "VehicleDynamics/t_TurretPointing.h"
#include "Motion/ArticulatedPartId.h"
#include "VehicleDynamics/Limits.h"

#ifdef WIN32
#ifdef MODULEOKTAL_EXPORTS
#define MODULEOKTAL_API __declspec(dllexport)
#else
#define MODULEOKTAL_API __declspec(dllimport)
#endif
#else
#define MODULEOKTAL_API 
#endif

#ifdef __cplusplus
extern "C" {
#else //__cplusplus
#define bool char
#endif //__cplusplus

#ifdef _MSC_VER
typedef __int64 LONG_LONG;
typedef unsigned __int64 CANALEG_INDEX;
#define OKTAL_DECL __cdecl
#else
typedef long long LONG_LONG;
typedef unsigned long long CANALEG_INDEX;
// TODO
#define OKTAL_DECL 
#endif


//return codes for OKTALFunctionOutput()
typedef enum
{
	TSimRestart = -1,
	TSimError = 0,
	TSimOK = 1
} t_SimCode;

//supported by Callas version 4.2 and later
#define FUNCTION_RUN							((LONG_LONG)1<<0)
#define FUNCTION_COMMAND_STEERING				((LONG_LONG)1<<1)
#define FUNCTION_COMMAND_PEDALS					((LONG_LONG)1<<2)
#define FUNCTION_COMMAND_TURRET					((LONG_LONG)1<<3)
#define FUNCTION_TURRET							((LONG_LONG)1<<4)
#define FUNCTION_ENGINE							((LONG_LONG)1<<5)
#define FUNCTION_WHEELS_ELASTICITY				((LONG_LONG)1<<6)
#define FUNCTION_FORCE							((LONG_LONG)1<<7)
#define FUNCTION_SOLID							((LONG_LONG)1<<8)
#define FUNCTION_GRIP							((LONG_LONG)1<<9)
//supported by Callas version 4.3 and later
#define FUNCTION_STEERING						((LONG_LONG)1<<10)
#define FUNCTION_WHEEL_TORSER					((LONG_LONG)1<<11)
//supported by Callas version 4.4 and later
#define FUNCTION_WIND							((LONG_LONG)1<<12)
#define FUNCTION_DEPRECATED1					((LONG_LONG)1<<13)
//supported by Callas version 4.5 and later
#define FUNCTION_BRAKE_PRESSURE					((LONG_LONG)1<<14)

//added for Callas Evos
#define FUNCTION_COMMAND_GEAR					((LONG_LONG)1<<15)
#define FUNCTION_COMMAND_SKID					((LONG_LONG)1<<16)
#define FUNCTION_COMPONENT_TRAVEL				((LONG_LONG)1<<17)
#define FUNCTION_WHEELS_KINEMATICS				((LONG_LONG)1<<18)
#define FUNCTION_TIRE_GRIP						((LONG_LONG)1<<19)
#define FUNCTION_TIRE_ELASTICITY				((LONG_LONG)1<<20)
#define FUNCTION_GROUND_PROPERTIES				((LONG_LONG)1<<21)
#define FUNCTION_WHEEL_STEERING					((LONG_LONG)1<<22)
#define FUNCTION_ROLLER_ELASTICITY				((LONG_LONG)1<<23)
#define FUNCTION_ROLLER_COMPONENT_TRAVEL		((LONG_LONG)1<<24)
#define FUNCTION_ROLLER_KINEMATICS				((LONG_LONG)1<<25)
#define FUNCTION_LINKS_GRIP						((LONG_LONG)1<<26)
#define FUNCTION_DEFECTS						((LONG_LONG)1<<27)
#define FUNCTION_THERMAL_ENGINE					((LONG_LONG)1<<28)
#define FUNCTION_THERMAL_SUSPENSION_WHEELS		((LONG_LONG)1<<29)
#define FUNCTION_THERMAL_BRAKES					((LONG_LONG)1<<30)
#define FUNCTION_THERMAL_TIRES					((LONG_LONG)1<<31)
#define FUNCTION_THERMAL_TRANSMISSION			((LONG_LONG)1<<32)
#define FUNCTION_CONVERTER						((LONG_LONG)1<<33)
#define FUNCTION_GEAR_BOX						((LONG_LONG)1<<34)
#define FUNCTION_BODY_AERODYNAMICS				((LONG_LONG)1<<35)
#define FUNCTION_WHEEL_AERODYNAMICS				((LONG_LONG)1<<36)
#define FUNCTION_RECOIL_FORCE					((LONG_LONG)1<<37)
#define FUNCTION_PLOW							((LONG_LONG)1<<38)
#define FUNCTION_GMP_TORQUE						((LONG_LONG)1<<39)
#define FUNCTION_TORSER_ROLLS					((LONG_LONG)1<<40)
#define FUNCTION_TORSER_TURRETS					((LONG_LONG)1<<41)
#define FUNCTION_TORSER_WEAPONS					((LONG_LONG)1<<42)
#define FUNCTION_TIRE_SENSOR					((LONG_LONG)1<<43)

//supported by Callas version 4.5 R109 and later
#define FUNCTION_COMMAND_GEAR_SUP				((LONG_LONG)1<<44)

//supported by Callas version 4.7 R22 and later
#define FUNCTION_DEPRECATED2					((LONG_LONG)1<<45)
#define FUNCTION_IGNITION_KEY					((LONG_LONG)1<<46)
#define FUNCTION_TOGGLE_ELECTRONIC_ASSISTANCE	((LONG_LONG)1<<47)
#define FUNCTION_SUSPENSION_NOTCH				((LONG_LONG)1<<48)
#define FUNCTION_VISUAL_APPEARANCE				((LONG_LONG)1<<49)

//supported by Callas version 4.7 R50 and later
#define FUNCTION_WATER_CURRENT					((LONG_LONG)1<<50)

//supported by Callas version 4.8 R15 and later
#define FUNCTION_PLOW_COMMAND					((LONG_LONG)1<<51)
#define FUNCTION_SUSPENSION_HEIGHT				((LONG_LONG)1<<52)
#define FUNCTION_RETARDER_COMMAND				((LONG_LONG)1<<53)

//supported by Callas version 4.8 R31 and later
#define FUNCTION_ADDITIONAL_STEERING_TORQ		((LONG_LONG)1<<54)

//supported by Callas version 4.9 R15 and later
#define FUNCTION_WHEEL_SOLID					((LONG_LONG)1<<55)

//supported by Callas/SCANeR studio 1.5 and later
#define FUNCTION_WHEELS							((LONG_LONG)1<<56)

#define FUNCTION_MOTOR_COMMAND					((LONG_LONG)1<<57)

//supported by Callas/SCANeR studio 1.9 update and later
#define FUNCTION_PILOTED_DIFF					((LONG_LONG)1<<58)


//OKTALOptions
#define OPTION_STEADYSTATE		(1<<0)	//the module can be used during steady-state
#define OPTION_DEFFERED_TIME	(1<<1)	//the module can be used during differed time
#define OPTION_REAL_TIME		(1<<2)	//the module can be used in real time
#define OPTION_PAUSE			(1<<3)	//the module can pause
#define OPTION_IMPOSE_TIME		(1<<4)	//the module specifies "setpoints" for the temps
#define OPTION_INTEGRATED_CFG	(1<<5)	//the module's configuration file is formatted according
										//to the OKTAL specifications to integrate a cfg file in
										//a OKTAL file
#define OPTION_SPECIFY_INIT		(1<<6)	//(obsolete!) the module will specify the initial conditions of the run
#define OPTION_ROAD_QUERY		(1<<7)	//the module exports the road query API

#pragma pack(push,1)


#define NB_WEAPONS_MAX 10
#define NB_ACCELEROMETERS_MAX 23
#define NB_ROLLERS_MAX 14
#define NB_LINKS_MAX 150
#define NB_PASSENGERS_MAX 9
#define NB_LASERS_MAX 6
#define NB_MVT_SENSORS_MAX 10

#define NB_DYNAMIC_GROUND_PTS 1600
#define NB_DYNAMIC_GROUND_TRIS 3200

#define NB_APPEARANCE_ELTS 32
#define NB_APPEARANCE_PARAMS 6

typedef char C_PATH[100];


typedef enum {TRefVehicle, TRefTurret, TRefWeapon, TRefGround, TRefCabin} t_Reference;

typedef struct
{
	double x, y;
} SPoint2D;

typedef struct
{
	double x, y, z;
} SPoint3D;

typedef struct
{
	double x, y, z;
	double roll, pitch, heading;
} SMark;

typedef struct
{
	SPoint3D PointOfApplication;
	SPoint3D Force;
	SPoint3D Moment;
} STorser;

typedef struct
{
	SPoint3D pos;
	SPoint3D norm;
	int laneType;
	int groundIndex;
} RoadQueryVal;

typedef struct
{
	SPoint2D Pos;
	double Heading;
	double Speed;
	double FuelTankRatio;
} InitCondition;

typedef struct
{
	int nbvhc;
	C_PATH NameTerrain;

	char rab[148]; //for compatibility with Callas 4.9
} InfoCalcul;

typedef struct
{
	int NbAxles;

	int	NbGears;
	int	NbReverseGears;
	double EmptyVhcCOGHeight;
	double SteeringWheelMax[2];

	double SprungMass;
	double UnsprungMass[NB_AXLES_MAX][2];
	double StaticLoad[NB_AXLES_MAX][2];

	bool	Abs;
	bool	Esp;
	bool	Asr;

	double HalfTrack[NB_AXLES_MAX][2];

//for the animation
	C_PATH rab5;

	bool rab0;
	C_PATH rab1[6];
	C_PATH rab6;
	C_PATH rab7;

	SPoint3D TracesColor;
	SPoint3D CurvesColor;
	SPoint3D PosPilotEye;
	SPoint3D BodyScale;

//tire description... by axel!
	C_PATH rab8[NB_AXLES_MAX];
	C_PATH rab9[NB_AXLES_MAX];
	C_PATH rab2[NB_AXLES_MAX]; //for compatibility with Callas 4.9

	double TreadWidth[NB_AXLES_MAX][2];
	double RimDiam[NB_AXLES_MAX][2];
	double MaxForce;
	double MaxForcePlow;
	double LengthForce;

	bool rab3; //for compatibility with Callas 4.9

	int NbOscMass;

	bool IsTwinWheels[NB_AXLES_MAX];
	bool IsRigidAxle[NB_AXLES_MAX];

	bool IsVhcTracks;
	bool IsTracksAxle[NB_AXLES_MAX];
	int NbRolls;
	double RollRadius[NB_ROLLERS_MAX];
	int NbLinks[2];
	double LinkWidth;
	double LinkThikness;

	C_PATH rab10;
	bool IsWithPlow;
	SPoint3D PlowScale;

	bool IsTurretActiv[NB_TURRETS_MAX];
	C_PATH rab11[NB_TURRETS_MAX];
	SPoint3D TurretScale[NB_TURRETS_MAX];
	SPoint3D TurretPosCdg[NB_TURRETS_MAX];

	bool IsWeaponActiv[NB_WEAPONS_MAX];
	C_PATH rab12[NB_WEAPONS_MAX];
	SPoint3D WeaponScale[NB_WEAPONS_MAX];
	SPoint3D WeaponPosCdg[NB_TURRETS_MAX];

	C_PATH rab13_1;

	bool IsLinkFront;
	SPoint3D PosLinkFront;
	bool IsLinkRear;
	SPoint3D PosLinkRear;
	SPoint3D PosPassengers[NB_PASSENGERS_MAX];

	int RefAccelero[NB_ACCELEROMETERS_MAX];
	int IndexAccelero[NB_ACCELEROMETERS_MAX];
	SPoint3D PosAccelero[NB_ACCELEROMETERS_MAX];

	SPoint3D PosCorrevit[2];
	SPoint3D PosGPSGyro;
	SPoint3D Overhang[2][5];
	SPoint3D UnderCarrige[4][2];

	double rab4[4]; //for compatibility with Callas 4.9

	double Wheelbase[NB_AXLES_MAX][2];
	double SteeringWheelDiameter;

	C_PATH rab13_2[NB_ROLLERS_MAX];
	double RollWidth[NB_ROLLERS_MAX];

	SPoint3D PassagerScale[NB_PASSENGERS_MAX];
	C_PATH PassengerName[NB_PASSENGERS_MAX];
	C_PATH rab5_1; //for compatibility with Callas 4.9

	SPoint3D PosLaserSensor[NB_LASERS_MAX];
	double StaticRideHeight[NB_AXLES_MAX];

	C_PATH PassengerModel[NB_PASSENGERS_MAX];

	SPoint3D PosPlowLink;

	SPoint3D PosRollerPivot[NB_ROLLERS_MAX][2];

	double WheelsMaxSteeringAngle[NB_AXLES_MAX][2][2];	//[axle][LeftOrRightWheel][LeftOrRightSteering]

	bool IsWithTorqueConverter;

	double userValue[10];

//new for SCANeR studio (not in Callas 4.9)
	C_PATH	NameAccelero[NB_ACCELEROMETERS_MAX];
	double engineSpeedMax;
	int nbWheelsPerAxle[NB_AXLES_MAX];
	C_PATH MdlName;

	SPoint3D PosHydrojet;

	int NbSupportRollers;
	double LinkLength;

	C_PATH rab15;
	bool IsWithCabin;
	SPoint3D CabinScale;

} VhcData;



/////////////////////////////////////////////////////////////////////
// EXPORTED FUNCTIONS
/////////////////////////////////////////////////////////////////////
//FUNCTION_RUN
typedef struct 
{
	bool IsRunning;
	bool IsAcquisition;
} FunctionOutputRun;

//FUNCTION_COMMAND_STEERING
typedef struct 
{
	bool	IsTorqCommand;
	double	SteeringTorq;

	double	SteeringWheelAngle;
	double	SteeringWheelSpeed;
	double	SteeringWheelAcc;

//supported by Callas version 4.5 and later
	double DistOnTraj;
	double IdealeCurvature;
	double TrajError;
	SPoint3D IdealTrjPos;
	SPoint3D IdealTrjDirection;
	SPoint3D PosPrevision;
} FunctionOutputCommandSteering;

//FUNCTION_COMMAND_PEDALS
typedef struct
{
	double	Accel; //[0.0 1.0]
	double	Brake; //  Force (N)
	double	HandBrake;// Force (N)
	double	Clutch;//[0.0 1.0]
} FunctionOutputCommandPedals;

//FUNCTION_COMMAND_TURRET
typedef struct
{
	int TypeArchitecture;

	int NbShots;
	double ShotRythm;
	t_TurretPointing TurretPointing;
	double AimAngTurret;
	double AimAngGun;
	SPoint3D TargetPosition;
	double	TurretSpeed;
	double	GunSpeed;
} FunctionOutputCommandTurret;

//FUNCTION_TURRET
typedef struct
{
	double TurretTorq;
	double GunTorq;
} FunctionOutputTurret;

//FUNCTION_ENGINE
typedef struct
{
	double EngineSpeed;
	double Torq;
	double PosAccelMesured;
	double InstantConsumption;
} FunctionOutputEngine;

//FUNCTION_WHEELS_ELASTICITY
typedef struct
{
	bool IsSpringExternalized[NB_AXLES_MAX][2];
	double ForceSpring[NB_AXLES_MAX][2];

	bool IsDamperExternalized[NB_AXLES_MAX][2];
	double ForceDamper[NB_AXLES_MAX][2];

	bool IsBumpCompExternalized[NB_AXLES_MAX][2];
	double ForceBumpComp[NB_AXLES_MAX][2];

	bool IsBumpReboundExternalized[NB_AXLES_MAX][2];
	double ForceBumpRebound[NB_AXLES_MAX][2];

	bool IsAntiRollBarExternalized[NB_AXLES_MAX][2];
	double ForceAntiRollBar[NB_AXLES_MAX][2];
} FunctionOutputWheelsElasticity;


// The external torser is defined by :
// - a Force
// - a Moment
// - a point of application
//all vectors are defined in the vehicle dynamics mark :
// X towards the front, Y to the left, Z upwards, centered at the CoG of the vehicle
//FUNCTION_FORCE
typedef struct
{
	STorser T;
} FunctionOutputForce;

//this function adds a solid to the vehicle
//with a masse, a position and a rotation inertia
//during the simulation
//FUNCTION_SOLID : defined in vehicle architect frame
typedef struct
{
	SPoint3D Pos;
	double Ixx, Iyy, Izz;
	double Ixy, Ixz, Iyz;
	double Mass;
} FunctionOutputSolid;

//FUNCTION_GRIP
typedef struct
{
	double GripLongi[NB_AXLES_MAX][2];
	double GripLateral[NB_AXLES_MAX][2];
} FunctionOutputGrip;

//FUNCTION_STEERING
typedef struct
{
    double RackTravel[NB_AXLES_MAX];
    double RackTravelSpeed[NB_AXLES_MAX];
    double RackTravelAcceleration[NB_AXLES_MAX];
 
	double PinionAngle;
    double PinionSpeed;
    double PinionAcceleration;

    double TorsionAngle;
    double AssistanceTorque;
} FunctionOutputSteering;

//FUNCTION_WHEEL_TORSER
typedef struct
{
	STorser TorserSup[NB_AXLES_MAX][2];
} FunctionOutputWheelTorser;

//FUNCTION_WIND
typedef struct
{
	double Direction;
	double Speed;
} FunctionOutputWind;

//FUNCTION_GROUND_GEOMETRY_2D
typedef struct
{
	int reserved;
} FunctionOutputDeprecated1;

//FUNCTION_BRAKE_PRESSURE
typedef struct
{
	double Pressure[NB_AXLES_MAX][2];
} FunctionOutputBrakePressure;

//FUNCTION_COMMAND_GEAR
typedef struct
{
	int		WantedGear;
	t_GearBoxAutoMode	AutoMode;
} FunctionOutputGearboxCommand;

//FUNCTION_COMMAND_SKID
typedef struct
{
	double	CommandSkid;
} FunctionOutputCommandSkid;

//FUNCTION_COMPONENT_TRAVEL
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX];
	double SpringTravel[NB_AXLES_MAX][2];
	double RatioKinSpring[NB_AXLES_MAX][2];
	double DamperTravel[NB_AXLES_MAX][2];
	double RatioKinDamper[NB_AXLES_MAX][2];
	double BumpCompTravel[NB_AXLES_MAX][2];
	double RatioKinBumpComp[NB_AXLES_MAX][2];
	double BumpReboundTravel[NB_AXLES_MAX][2];
	double RatioKinBumpRebound[NB_AXLES_MAX][2];
} FunctionOutputComponentTravel;

//FUNCTION_WHEELS_KINEMATICS
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX];
	SPoint2D Position[NB_AXLES_MAX][2];
	SPoint3D Angle[NB_AXLES_MAX][2];
	SPoint2D PositionDerivative[NB_AXLES_MAX][2];
	SPoint3D AngleDerivative[NB_AXLES_MAX][2];
} FunctionOutputWheelKinematics;

//FUNCTION_TIRE_GRIP
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX][2][2];
	SPoint2D Force[NB_AXLES_MAX][2][2];
	SPoint3D Moment[NB_AXLES_MAX][2][2];
} FunctionOutputTireGrip;

//FUNCTION_TIRE_ELASTICITY
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX][2][2];
	double VerticalForce[NB_AXLES_MAX][2][2];
} FunctionOutputTireElasticity;

//FUNCTION_GROUND_PROPERTIES
typedef struct
{
	int Properties[2];
} FunctionOutputGroundProperties;

//FUNCTION_WHEEL_STEERING
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX];
	double SteeringAngle[NB_AXLES_MAX][2];
} FunctionOutputWheelSteering;

//Roller order:
//1. the pulley (optionnaly)
//2. the sprocket
//3. the bearing rollers
//4. the support rollers

//FUNCTION_ROLLER_ELASTICITY
typedef struct
{
	bool IsSpringExternalized[NB_ROLLERS_MAX][2];
	double ForceSpring[NB_ROLLERS_MAX][2];
	bool IsDamperExternalized[NB_ROLLERS_MAX][2];
	double ForceDamper[NB_ROLLERS_MAX][2];
	bool IsBumpCompExternalized[NB_ROLLERS_MAX][2];
	double ForceBumpComp[NB_ROLLERS_MAX][2];
	bool IsBumpReboundExternalized[NB_ROLLERS_MAX][2];
	double ForceBumpRebound[NB_ROLLERS_MAX][2];
} FunctionOutputRollerElasticity;

//FUNCTION_ROLLER_COMPONENT_TRAVEL
typedef struct
{
	bool IsExternalized[NB_ROLLERS_MAX][2];
	double SpringTravel[NB_ROLLERS_MAX][2];
	double SpringKinRatio[NB_ROLLERS_MAX][2];
	double DamperTravel[NB_ROLLERS_MAX][2];
	double DamperKinRatio[NB_ROLLERS_MAX][2];
	double BumpCompTravel[NB_ROLLERS_MAX][2];
	double BumpCompKinRatio[NB_ROLLERS_MAX][2];
	double BumpReboundTravel[NB_ROLLERS_MAX][2];
	double BumpReboundKinRatio[NB_ROLLERS_MAX][2];
} FunctionOutputRollerComponentTravel;

//FUNCTION_ROLLER_KINEMATICS
typedef struct
{
	bool IsExternalized[NB_ROLLERS_MAX][2];
	SPoint3D Positions[NB_ROLLERS_MAX][2];
	SPoint3D Angles[NB_ROLLERS_MAX][2];
	SPoint3D PositionsDerivative[NB_ROLLERS_MAX][2];
	SPoint3D AnglesDerivative[NB_ROLLERS_MAX][2];
} FunctionOutputRollerKinematics;

//FUNCTION_LINKS_GRIP
typedef struct
{
	SPoint2D Force[NB_LINKS_MAX][2];
} FunctionOutputLinksGrip;

//FUNCTION_DEFECTS
typedef struct
{
	bool IsDefEngine;
	double EngineTorq;
	
	bool IsDefConverter;
	double InvariantConverter;

	bool IsDefSteeringAssistance;
	double SteeringTorqAssistance;

	bool IsDefTires;
	double TireStiffness [NB_AXLES_MAX][2][2];
	double TirePressure [NB_AXLES_MAX][2][2];
	double TireGripLongi [NB_AXLES_MAX][2][2];
	double TireGripLat [NB_AXLES_MAX][2][2];

	bool IsDefSuspWheels;
	double WheelDamperComp [NB_AXLES_MAX][2];
	double WheelDamperRebound [NB_AXLES_MAX][2];
	double WheelBumpComp [NB_AXLES_MAX][2];
	double WheelBumpRebound [NB_AXLES_MAX][2];
	double WheelElasticityForce [NB_AXLES_MAX][2];

	bool IsDefBrake;
	double BrakeTorq [NB_AXLES_MAX][2];
	double BrakePressure [NB_AXLES_MAX][2];

	bool IsDefSuspRolls;
	double RollDamperComp	[NB_ROLLERS_MAX][2];
	double RollDamperRebound	[NB_ROLLERS_MAX][2];
	double RollBumpComp	[NB_ROLLERS_MAX][2];
	double RollBumpRebound	[NB_ROLLERS_MAX][2];
	double RollElasticityForce [NB_ROLLERS_MAX][2];
} FunctionOutputDefects;

//FUNCTION_THERMAL_ENGINE
typedef struct
{
	double TempWater;
	double TempOil;
} FunctionOutputThermalEngine;

//FUNCTION_THERMAL_SUSPENSION_WHEELS
typedef struct
{
	double TempDamper[NB_AXLES_MAX][2];
} FunctionOutputThermalSuspensionWheels;

//FUNCTION_THERMAL_BRAKES
typedef struct
{
	double TempDiscs[NB_AXLES_MAX][2];
} FunctionOutputThermalBrakes;

//FUNCTION_THERMAL_TIRES
typedef struct
{
	double TempTires[NB_AXLES_MAX][2][2];
} FunctionOutputThermalTires;

//FUNCTION_THERMAL_TRANSMISSION
typedef struct
{
	double TempGearBox;
	double TempClutch;
} FunctionOutputThermalTransmission;

//FUNCTION_CONVERTER
typedef struct
{
	double TorqIn;
	double TorqOut;
	double TurbineInertia;
	double PumpInertia;
} FunctionOutputConverter;

//FUNCTION_GEAR_BOX
typedef struct
{
	double TorqIn;
	double TorqOut;
	double Demul;
	double Yield;
	double Inertia;
} FunctionOutputGearBox;

//FUNCTION_BODY_AERODYNAMICS
typedef struct
{
	STorser TorserBody;
	double Cx;
	double Cy1;
	double Cy2;
	double Cz1;
	double Cz2;
	double Cl;
} FunctionOutputBodyAerodynamics;

//FUNCTION_WHEEL_AERODYNAMICS
typedef struct
{
	STorser WheelTorser[NB_AXLES_MAX][2];
} FunctionOutputWheelAerodynamics;

//FUNCTION_RECOIL_FORCE
typedef struct
{
	double Effort;
	double RecoilDist;
} FunctionOutputRecoilForce;

//FUNCTION_PLOW
typedef struct
{
	STorser PlowTorser;
} FunctionOutputPlow;

//FUNCTION_GMP_TORQUE
typedef struct
{
	double TorqSupEngine;
	double TorqSupClutch;
	double TorqSupGearBox;
} FunctionOutputGMPTorque;

//FUNCTION_TORSER_ROLLS
typedef struct
{
	STorser TorserSup[NB_ROLLERS_MAX][2];
} FunctionOutputTorserRolls;

//FUNCTION_TORSER_TURRETS
typedef struct
{
	STorser TorserSup[NB_TURRETS_MAX];
} FunctionOutputTorserTurrets;

//FUNCTION_TORSER_WEAPONS
typedef struct
{
	STorser TorserSup[NB_WEAPONS_MAX];
} FunctionOutputTorserWeapons;

//FUNCTION_TIRE_SENSOR
typedef struct
{
	bool IsExternalized[NB_AXLES_MAX][2][2];
	SMark Contact[NB_AXLES_MAX][2][2];
} FunctionOutputTireSensor;


typedef enum {TEngineRetarderOff, TEngineRetarderOn} t_EngineRetarder;
typedef enum {TAdditionalTorqAssit, TAdditionalTorqWheelSteering} t_AdditionalTorq;

//FUNCTION_COMMAND_GEAR_SUP
typedef struct
{
	t_TransferChoice	TransferChoice;
	t_LockDiffMode		LockDiffMode;
	bool				ForceLockup;
} FunctionOutputGearboxCommandSup;


typedef enum {TGroundNoOp, TGroundAdd, TGroundReplace} t_DynamicGroundMode;

typedef struct
{
	unsigned char type; //index of the ground type as defined in the *.sol file
	short index[3]; //indices of the triangle points 0<=index<NB_DYNAMIC_GROUND_PTS
	short neighbor[3]; //indices of the neighboring triangles 0<=index<NB_DYNAMIC_GROUND_TRIS
} GroundTri;

//FUNCTION_GROUND_GEOMETRY_3D
typedef struct
{
	int reserved;
} FunctionOutputDeprecated2;

//FUNCTION_IGNITION_KEY
typedef struct
{
	t_IgnitionKeyPosition KeyPosition;
} FunctionOutputIgnitionKey;

//FUNCTION_TOGGLE_ELECTRONIC_ASSISTANCE
typedef struct
{
	bool EnableABS;
	bool EnableTractionControl;
	bool EnableESP;
} FunctionOutputToggleElectronicAssistance;

//FUNCTION_SUSPENSION_NOTCH
typedef struct
{
	double SpringNotch[NB_AXLES_MAX][2];
	double BumpDamperNotch[NB_AXLES_MAX][2];
	double ReboundDamperNotch[NB_AXLES_MAX][2];
	double CentralSpringNotch[NB_AXLES_MAX];
	double CentralBumpDamperNotch[NB_AXLES_MAX];
	double CentralReboundDamperNotch[NB_AXLES_MAX];
} FunctionOutputSuspensionNotch;


typedef enum {TAppearNone, TAppearLine, TAppearSphere, TAppearCylinder, TAppearCube, TAppearMark} t_AppearanceElt;

typedef struct
{
	t_ArticulatedPartId id;
	t_Reference Reference;
	t_AppearanceElt type;
	SMark pos;
	SMark speed;
	SMark accel;
	SPoint3D color;
	double params[NB_APPEARANCE_PARAMS];
} AppearanceElt;

//FUNCTION_VISUAL_APPEARANCE
typedef struct
{
	AppearanceElt Elts[NB_APPEARANCE_ELTS];
} FunctionOutputVisualAppearance;

//FUNCTION_WATER_CURRENT
typedef struct
{
	double Direction; //direction of the water current
	double Speed; //speed of the water current
	double Altitude; //altitude of the water level
} FunctionOutputWaterCurrent;

//FUNCTION_PLOW_COMMAND
typedef struct
{
	t_PlowMode	PlowMode;
} FunctionOutputPlowCommand;	

//FUNCTION_SUSPENSION_HEIGHT
typedef struct
{
	bool	EnableRegulation[NB_AXLES_MAX][2];	//True to activate the suspension regulation, false to lock actual the setting
	double	SuspensionOffset[NB_AXLES_MAX][2];	//Positive value to raise the vehicule's body
} FunctionOutputSuspensionHeight;

//FUNCTION_RETARDER_COMMAND
typedef struct
{
	t_EngineRetarder EngineRetarderCommand;
	double BrakeRetarderNotch;
} FunctionOutputRetarderCommand;

//FUNCTION_ADDITIONAL_STEERING_TORQ
typedef struct 
{
	t_AdditionalTorq AdditionalTorqType;
	double AdditionalTorq;
} FunctionOutputAdditionalSteeringTorq;

//FUNCTION_WHEEL_SOLID
typedef struct 
{
	bool isExternalized[NB_AXLES_MAX][2];
	double wheelInertia[NB_AXLES_MAX][2];
}FunctionOutputWheelSolid;

//FUNCTION_WHEELS
typedef struct
{
	bool isExternalized[NB_AXLES_MAX][2];
	double wheelAcceleration[NB_AXLES_MAX][2];
	double wheelSpeed[NB_AXLES_MAX][2];
	double wheelRotation[NB_AXLES_MAX][2];
} FunctionOutputWheels;

//FUNCTION_MOTOR_COMMAND
typedef struct
{
	bool iceIgnitionOn;
	bool iceStarterMotor;
	double iceThrottle;
	double wheelElectricMotorCommand[NB_AXLES_MAX][2];
	double differentialElectricMotorCommand[20];
} FunctionOutputMotorCommand;

//FUNCTION_PILOTED_DIFF
typedef struct
{
	bool isPilotedDiff[20];
	double diffRepartition[20];
} FunctionOutputPilotedDiff;

#pragma pack(pop)

typedef void (OKTAL_DECL *LogFunction)(const char* text);
typedef int (OKTAL_DECL *RQPickFunction)(void* rq, int sensor, SPoint3D pickingPos, RoadQueryVal* out);

MODULEOKTAL_API void OKTAL_DECL OKTALSetLogFunction(LogFunction Func); //supported by version 4.3 and later
MODULEOKTAL_API void OKTAL_DECL OKTALSetRQPickFunction(void* PrivateStruct, RQPickFunction Func, void* rq, int sensor); //supported by version SCANEeR studio 1.4 and later
MODULEOKTAL_API const char* OKTAL_DECL OKTALName();
MODULEOKTAL_API int OKTAL_DECL OKTALOptions();
MODULEOKTAL_API void* OKTAL_DECL OKTALNewPrivateStruct(const char* NomConfig);
MODULEOKTAL_API int OKTAL_DECL OKTALGetCustomGraphCount(void* PrivateStruct);
MODULEOKTAL_API const char* OKTAL_DECL OKTALGetCustomGraphName(void* PrivateStruct, int index);
MODULEOKTAL_API const char* OKTAL_DECL OKTALGetCustomGraphUnit(void* PrivateStruct, int index);
MODULEOKTAL_API bool OKTAL_DECL OKTALGetInitCondition(void* PrivateStruct, InitCondition* condition, int conditionsize);
MODULEOKTAL_API bool OKTAL_DECL OKTALInitCalcul(void* PrivateStruct, InfoCalcul* data);
MODULEOKTAL_API void OKTAL_DECL OKTALIdle(void* PrivateStruct);
MODULEOKTAL_API bool OKTAL_DECL OKTALInitVhc(void* PrivateStruct, int novhc, VhcData* data, int datasize);
MODULEOKTAL_API void OKTAL_DECL OKTALStart(void* PrivateStruct);
MODULEOKTAL_API int OKTAL_DECL OKTALGetReady(void* PrivateStruct);
MODULEOKTAL_API void OKTAL_DECL OKTALResume(void* PrivateStruct);
MODULEOKTAL_API double OKTAL_DECL OKTALPeriode(void* PrivateStruct);
MODULEOKTAL_API LONG_LONG OKTAL_DECL OKTALExportedFunctions(void* PrivateStruct, int novhc);
MODULEOKTAL_API void OKTAL_DECL OKTALChannelsNeeded(void* PrivateStruct, int* NbChannels, CANALEG_INDEX** Channels);
MODULEOKTAL_API void OKTAL_DECL OKTALInput(void* PrivateStruct, int novhc, double* Input);
MODULEOKTAL_API void OKTAL_DECL OKTALStep(void* PrivateStruct, double DeltaT);
MODULEOKTAL_API double OKTAL_DECL OKTALGetTimeSetpoint(void* PrivateStruct); //supported by version 4.4 and later
MODULEOKTAL_API t_SimCode OKTAL_DECL OKTALFunctionOutput(void* PrivateStruct, int novhc, LONG_LONG FunctionNumber, int* OutputSize, void* Output);
MODULEOKTAL_API void OKTAL_DECL OKTALPause(void* PrivateStruct);
MODULEOKTAL_API void OKTAL_DECL OKTALStop(void* PrivateStruct);

//DEPRECATED: SERASetErrorMsg()
//MODULESERA_API void OKTAL_DECL OKTALSetErrorMsg(void* PrivateStruct, const char* Message); //supported by version 4.7 and later

MODULEOKTAL_API t_SimCode OKTAL_DECL OKTALSetErrorMessage(void* PrivateStruct, const char* Message, int reserved); //supported by version 4.7 and later
MODULEOKTAL_API const char* OKTAL_DECL OKTALGetErrorMessage(void* PrivateStruct); //supported by version 4.7 and later

MODULEOKTAL_API int OKTAL_DECL OKTALGetUnReady(void* PrivateStruct); //not yet supported
MODULEOKTAL_API void OKTAL_DECL OKTALDeletePrivateStruct(void* PrivateStruct);
MODULEOKTAL_API int OKTAL_DECL OKTALGetWindowHandle(void* PrivateStruct);
MODULEOKTAL_API const char* OKTAL_DECL OKTALGetState(void* PrivateStruct);


#ifdef __cplusplus
}

class QWidget;

extern "C" MODULEOKTAL_API int OKTAL_DECL OKTALEditConfig(QWidget* Parent, char* NomConfig);

#endif //__cplusplus

#endif //_CAL_MODULE_H_
