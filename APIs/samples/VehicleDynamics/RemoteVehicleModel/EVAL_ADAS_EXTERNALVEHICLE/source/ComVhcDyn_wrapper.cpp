

/*
 * Include Files
 *
 */
#include "simstruc.h"


/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <assert.h>
#include "source/ComVhcDynHelper.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 3
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
//extern int timesTwo(real_T* a, real_T b);
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void ComVhcDyn_Outputs_wrapper(const real_T *pos,
			const real_T *roll,
			const real_T *pitch,
			const real_T *heading,
			const real_T *speed,
			const real_T *accel,
			const real_T *engineStatus,
			const real_T *engineSpeed,
			const real_T *effectiveSteeringWheelAngle,
			const real_T *SteeringWheelFeedbackTorque,
			const real_T *effectiveGasPedalPos,
			const real_T *effectiveBrake,
			const real_T *effectiveHandBrake,
			const real_T *effectiveClutch,
			const real_T *effectiveGearEngaged,
			const real_T *effectiveGearBoxMode,
			const real_T *effectiveIgnitionKeyPosition,
			const real_T *effectiveConsumption,
			const real_T *isEngineRetarder,
			const real_T *effectiveBrakeRetarderNotch,
			const real_T *effectiveTrailerBrake,
			const real_T *effectiveTransferChoice,
			const real_T *effectiveLockDiffMode,
			const real_T *effectiveForceLockup,
			const real_T *effectivePlowMode,
			const real_T *effectiveHorn,
			const real_T *effectiveLights,
			const real_T *effectiveRearWiperState,
			const real_T *effectiveFrontWiperState,
			const real_T *reserved1,
			const real_T *reserved2,
			const real_T *effectiveBatteryStateOfCharge,
			const real_T *wheel0,
			const real_T *wheel1,
			const real_T *wheel2,
			const real_T *wheel3,
			const real_T *electricMotor0,
			const real_T *electricMotor1,
			const real_T *electricMotor2,
			const real_T *electricMotor3,
			const real_T *electricMotor4,
			const real_T *electricMotor5,
			const real_T *electricMotor6,
			const real_T *customVehicleOutput,
			const real_T *synchronizedValue,
			real_T *initHeading,
			real_T *initSpeed,
			real_T *initGroundPos,
			real_T *initGroundNorm,
			real_T *enableCommandOverride,
			real_T *steeringWheel,
			real_T *steeringWheelSpeed,
			real_T *accelerator,
			real_T *brake,
			real_T *clutch,
			real_T *wantedGear,
			real_T *gearBoxAutoMode,
			real_T *shiftUp,
			real_T *shiftDown,
			real_T *ignitionKey,
			real_T *parkingBrake,
			real_T *fowa,
			real_T *telma,
			real_T *indicators,
			real_T *lights,
			real_T *rearWiperState,
			real_T *frontWiperState,
			real_T *horn,
			real_T *warnings,
			real_T *frontFogLights,
			real_T *rearFogLights,
			real_T *trailerBrake,
			real_T *rVLVState,
			real_T *rVLVTarget,
			real_T *transferChoice,
			real_T *lockDiffMode,
			real_T *rain,
			real_T *snow,
			real_T *windHeading,
			real_T *windVelocity,
			real_T *temperature,
			real_T *externalTorserApplicationPoint,
			real_T *externalTorserForce,
			real_T *externalTorserMoment,
			real_T *wheelSensor0,
			real_T *wheelSensor1,
			real_T *wheelSensor2,
			real_T *wheelSensor3,
			real_T *customVehicleInput,
			SimStruct *S)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
ComUdpState stateSimulation = ComVhcDynStep(
	ssGetT(S),
//DATA INPUTS PORTS
	//Vehicle outputs
	pos,
	roll,
	pitch,
	heading,
	speed,
	accel,
	engineStatus,
	engineSpeed,
	//Effective commands
	effectiveSteeringWheelAngle,
	SteeringWheelFeedbackTorque,
	effectiveGasPedalPos,
	effectiveBrake,
	effectiveHandBrake,
	effectiveClutch,
	effectiveGearEngaged,
	effectiveGearBoxMode,
	effectiveIgnitionKeyPosition,
	effectiveConsumption,
	isEngineRetarder,
	effectiveBrakeRetarderNotch,
	effectiveTrailerBrake,
	effectiveTransferChoice,
	effectiveLockDiffMode,
	effectiveForceLockup,
	effectivePlowMode,
	effectiveHorn,
	effectiveLights,
	effectiveRearWiperState,
	effectiveFrontWiperState,
	reserved1,
	reserved2,
	effectiveBatteryStateOfCharge,
	//wheels data
	wheel0,
	wheel1,
	wheel2,
	wheel3,
	//electric motor
	electricMotor0,
	electricMotor1,
	electricMotor2,
	electricMotor3,
	electricMotor4,
	electricMotor5,
	electricMotor6,
	//custom
	customVehicleOutput,
	//synchro
	synchronizedValue,
//DATA INPUTS PORTS
    //initial conditions
	initHeading,
	initSpeed,
	initGroundPos,
	initGroundNorm,
    //real time simulation data
	enableCommandOverride,
    //SCANeR driver inputs
	steeringWheel,
	steeringWheelSpeed,
	accelerator,
	brake,
	clutch,
	wantedGear,
	gearBoxAutoMode,
    shiftUp,
    shiftDown,
	ignitionKey,
	parkingBrake,
	fowa,
	telma,
	indicators,
	lights,
	rearWiperState,
	frontWiperState,
	horn,
	warnings,
	frontFogLights,
	rearFogLights,
	trailerBrake,
	rVLVState,
	rVLVTarget,
    transferChoice,
    lockDiffMode,
    //environment data
    rain,
    snow,
    windHeading,
    windVelocity,
    temperature,
    externalTorserApplicationPoint,
    externalTorserForce,
    externalTorserMoment,
    //wheels data
	wheelSensor0,
	wheelSensor1,
	wheelSensor2,
	wheelSensor3,
    //custom
    customVehicleInput);

	if (stateSimulation == CUS_STOP_SIMULATION)
	{
        ssSetStopRequested(S, 1);
		return;
	}

	if (stateSimulation == CUS_ERROR_INIT_TIMEOUT)
	{
		ssSetErrorStatus(S, "Timeout while waiting for SCANeR to start simulation");
		return;
	}

	if (stateSimulation == CUS_ERROR_RUNTIME_TIMEOUT)
	{
		ssSetErrorStatus(S, "Timeout while waiting for SCANeR during simulation");
		return;
	}

	if (stateSimulation == CUS_ERROR_SOCKET)
	{
		ssSetErrorStatus(S, "Error while opening socket to communicate with SCANeRwarning");
		return;
	}

	if (stateSimulation == CUS_ERROR_PACKET_NUMBER)
	{
		ssSetErrorStatus(S, "Error Wrong packet number");
		return;
	}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}
