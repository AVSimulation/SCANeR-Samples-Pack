
#pragma once
enum ComUdpState 
{
	CUS_CONTINUE,
	CUS_STOP_SIMULATION,
	CUS_ERROR_SOCKET,
	CUS_ERROR_INIT_TIMEOUT,
	CUS_ERROR_RUNTIME_TIMEOUT,
	CUS_ERROR_PACKET_NUMBER
};

ComUdpState ComVhcDynStep(
	real_T time,
//DATA INPUTS PORTS
	//Vehicle outputs
	const real_T *pos,
	const real_T *roll,
	const real_T *pitch,
	const real_T *heading,
	const real_T *speed,
	const real_T *accel,
	const real_T *engineStatus,
	const real_T *engineSpeed,
	//Effective commands
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
	//wheels data
	const real_T *wheel0,
	const real_T *wheel1,
	const real_T *wheel2,
	const real_T *wheel3,
	//electric motor
	const real_T *electricMotor0,
	const real_T *electricMotor1,
	const real_T *electricMotor2,
	const real_T *electricMotor3,
	const real_T *electricMotor4,
	const real_T *electricMotor5,
	const real_T *electricMotor6,
	//custom
	const real_T *customVehicleOutput,
	//synchro
	const real_T *synchronizedValue,
//DATA INPUTS PORTS
	//initial conditions
	real_T *initHeading,
	real_T *initSpeed,
	real_T *initGroundPos,
	real_T *initGroundNormal,
	//real time simulation data
	real_T *enableCommandOverride,
	//SCANeR driver inputs
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
	real_T *rVLVSpeed,
	real_T *transferChoice,
	real_T *lockDiffMode,
	//environment data
	real_T *rain,
	real_T *snow,
	real_T *windHeading,
	real_T *windVelocity,
	real_T *temperature,
	real_T *externalTorserApplicationPoint,
	real_T *externalTorserForce,
	real_T *externalTorserMoment,
	//wheels data
	real_T *wheelSensor0,
	real_T *wheelSensor1,
	real_T *wheelSensor2,
	real_T *wheelSensor3,
	//custom
	real_T *customVehicleInput
);
