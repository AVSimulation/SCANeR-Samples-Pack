
#define real_T double

#include <math.h>
#include <float.h>
#include "ComVhcDynHelper.h"
#include "cal_reseau.h"
#include "cal_timer.h"
#include "VehicleDynamics/VehicleUDPPackets.h"
#include <iostream>
#include <string.h>

#pragma comment(lib, "ws2_32")

HSocServer* mSocket = NULL;
Timer mTimeLastPacketRecieved;
int packetCount = 0;
double scanerTime = 0;
const double timeOut = 10.0;
const double initTimeout = 60.0;
bool initDone = false;
bool synchronized = false;
bool firstDynamicPacketRecieved = false;
bool delayPacketSend = false;
bool terminateRequested = false;


void cleanupUdp()
{
    delete mSocket;
	mSocket = NULL;
    packetCount = 0;
   	scanerTime = 0;
    initDone = false;
    synchronized = false;
	firstDynamicPacketRecieved = false;
	delayPacketSend = false;
}

void assign(real_T *wheelSensor, ModelInputWheelPk* wheelIn)
{
	wheelSensor[0] = wheelIn->contactPosition[0];
	wheelSensor[1] = wheelIn->contactPosition[1];
	wheelSensor[2] = wheelIn->contactPosition[2];
	wheelSensor[3] = wheelIn->contactNormal[0];
	wheelSensor[4] = wheelIn->contactNormal[1];
	wheelSensor[5] = wheelIn->contactNormal[2];
	wheelSensor[6] = wheelIn->grip;
	wheelSensor[7] = wheelIn->groundIndex;
	wheelSensor[8] = wheelIn->laneType;
}

void assign(ModelOutputWheelPk* wheelOut, const real_T *wheel)
{
	wheelOut->hubPosition[0] = wheel[0];
	wheelOut->hubPosition[1] = wheel[1];
	wheelOut->hubPosition[2] = wheel[2];
	wheelOut->hubPosition[3] = wheel[3];
	wheelOut->hubPosition[4] = wheel[4];
	wheelOut->hubPosition[5] = wheel[5];
	wheelOut->wheelRotationSpeed = wheel[6];
	wheelOut->wheelAngle = wheel[7];
	wheelOut->vhlSx = wheel[8];
	wheelOut->vhlDelta = wheel[9];
}

void assign(ModelOutputElectricMotorPk* electricMotorOut, const real_T *electricMotor)
{
	electricMotorOut->speed = electricMotor[0];
	electricMotorOut->load = electricMotor[1];
	electricMotorOut->current = electricMotor[2];
}



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
	real_T *rVLVTarget,
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
)
{
	if (time==0)
	{
		cleanupUdp();
		terminateRequested = false;
	}
	if (terminateRequested)
	{
		terminateRequested = false;
		return CUS_STOP_SIMULATION;
	}

	if (!initDone)
	{
		synchronized = *synchronizedValue > 0.0;
		std::cout << "initializing (Simulink time=" << time << ", synchronized=" << std::boolalpha << synchronized << ")" << std::endl;
		if (mSocket==NULL)
		{
			mSocket = new HSocServer(MODEL_SYSTEM_PORT);
			if (synchronized)
			{
				mSocket->SetBlocking(true);
				mSocket->SetTimeout(initTimeout);
			}
			else
			{
				mSocket->SetBlocking(false);
			}
            if (mSocket->good())
                std::cout << "successfully opened socket " << MODEL_SYSTEM_PORT << " for comunication with SCANeR" << std::endl;
		}
		mTimeLastPacketRecieved.Event();
		scanerTime = 0;
		packetCount = 0;
		initDone = true;
	}

	if (mSocket==NULL || !mSocket->good())
	{
		std::cout << "Error : failed to open socket " << MODEL_SYSTEM_PORT << " for communication with SCANeR" << std::endl;
		cleanupUdp();
		terminateRequested = true;
		return CUS_ERROR_SOCKET;
	}

	char outbuf[sizeof(ModelOutputPk) + 4 * sizeof(ModelOutputWheelPk)/*174*8*/ + 7 * sizeof(ModelOutputElectricMotorPk)];
	memset(&outbuf, 0, sizeof(outbuf));
//fill the output packet in case we need to send it
	{
		ModelOutputPk* out = (ModelOutputPk*)&outbuf[0];
		out->packetNumber = packetCount;
		out->packetID = MODEL_OUTPUT_PK;
		out->protocolVersion = PROTOCOL_VERSION;
		out->errorCode = 0;
		out->vehicleModelSimulationTime = time;
		//DATA INPUTS PORTS
		//Vehicle outputs
		for (int i=0 ; i<3 ; i++)
			out->pos[i] = pos[i];
		out->roll = *roll;
		out->pitch = *pitch;
		out->heading = *heading;
		for (int i=0 ; i<6 ; i++)
			out->speed[i] = speed[i];
		for (int i=0 ; i<6 ; i++)
			out->accel[i] = accel[i];
		out->engineStatus = (int)*engineStatus;
		out->engineSpeed = *engineSpeed;
		//Effective commands
		out->effectiveSteeringWheelAngle = *effectiveSteeringWheelAngle;
		out->SteeringWheelFeedbackTorque = *SteeringWheelFeedbackTorque;
		out->effectiveGasPedalPos = *effectiveGasPedalPos;
		out->effectiveBrake = *effectiveBrake;
		out->effectiveHandBrake = *effectiveHandBrake;
		out->effectiveClutch = *effectiveClutch;
		out->gearEngaged = (int)*effectiveGearEngaged;
		out->GearBoxMode = (int)*effectiveGearBoxMode;
		out->effectiveIgnitionKeyPosition = (int)*effectiveIgnitionKeyPosition;
		out->consumption = *effectiveConsumption;
		out->isEngineRetarder = (*isEngineRetarder) != 0;
		out->brakeRetarderNotch = *effectiveBrakeRetarderNotch;
		out->trailerBrake = *effectiveTrailerBrake;
		out->transferChoice = (int)*effectiveTransferChoice;
		out->lockDiffMode = (int)*effectiveLockDiffMode;
		out->forceLockup = (*effectiveForceLockup) != 0;
		out->plowMode = (int)*effectivePlowMode;
		out->horn = (*effectiveHorn) != 0;
		out->lights = (int)*effectiveLights;
		out->rearWiperState = (int)*effectiveRearWiperState;
		out->frontWiperState = (int)*effectiveFrontWiperState;
		out->reserved1 = (int)*reserved1;
		out->reserved2 = (int)*reserved2;
		out->batteryStateOfCharge = (int)*effectiveBatteryStateOfCharge;
		//electric motor
		out->electricMotorNumber = 7;
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 0 * sizeof(ModelOutputElectricMotorPk)], electricMotor0);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 1 * sizeof(ModelOutputElectricMotorPk)], electricMotor1);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 2 * sizeof(ModelOutputElectricMotorPk)], electricMotor2);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 3 * sizeof(ModelOutputElectricMotorPk)], electricMotor3);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 4 * sizeof(ModelOutputElectricMotorPk)], electricMotor4);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 5 * sizeof(ModelOutputElectricMotorPk)], electricMotor5);
		assign((ModelOutputElectricMotorPk*)&outbuf[sizeof(ModelOutputPk) + 6 * sizeof(ModelOutputElectricMotorPk)], electricMotor6);
		//wheels data
		out->wheelNumber = 4;
		assign((ModelOutputWheelPk*)&outbuf[sizeof(ModelOutputPk)+ 7 * sizeof(ModelOutputElectricMotorPk) + 0*sizeof(ModelOutputWheelPk)], wheel0);
		assign((ModelOutputWheelPk*)&outbuf[sizeof(ModelOutputPk)+ 7 * sizeof(ModelOutputElectricMotorPk) + 1*sizeof(ModelOutputWheelPk)], wheel1);
		assign((ModelOutputWheelPk*)&outbuf[sizeof(ModelOutputPk)+ 7 * sizeof(ModelOutputElectricMotorPk) + 2*sizeof(ModelOutputWheelPk)], wheel2);
		assign((ModelOutputWheelPk*)&outbuf[sizeof(ModelOutputPk)+ 7 * sizeof(ModelOutputElectricMotorPk) + 3*sizeof(ModelOutputWheelPk)], wheel3);
		//custom
		for (int i = 0; i<NB_CUSTOM_OUTPUT_MAX; i++)
			out->customVehicleOutput[i] = customVehicleOutput[i];
	}

	if (delayPacketSend)
	{
		bool res = mSocket->Send(&outbuf, sizeof(outbuf));
		++packetCount;
	}

	char inbuff[sizeof(ModelInputPk)+4*sizeof(ModelInputWheelPk)];
	memset(inbuff, 0, sizeof(inbuff));
	ModelInputPk* in = (ModelInputPk*)&inbuff[0];
	

	bool dataReceived = false;
	if (packetCount == 0)
		std::cout << "Waiting for SCANeR Studio" << std::endl;
	if (synchronized)
	{
		mSocket->SetTimeout(packetCount>0 ? timeOut : initTimeout);
		int receive = mSocket->Recieve(inbuff, sizeof(inbuff));
		dataReceived = receive==sizeof(inbuff);
        if (dataReceived)
		{
			if (in->protocolVersion==PROTOCOL_VERSION && in->packetID==MODEL_INPUT_PK)
			{
				if (in->simulationMode == SIM_MODE_INITIALIZE)
					delayPacketSend = true;
				else if (in->packetNumber != packetCount)
				{
					std::cout << "ERROR : Wrong packet number, is " << in->packetNumber << " but should be " << packetCount  << ", terminating simulation" << std::endl;
					terminateRequested = true;
					return CUS_ERROR_PACKET_NUMBER;
				}
			}
		}
        else //!dataReceived
        {
             cleanupUdp();
			terminateRequested = true;
			return CUS_ERROR_RUNTIME_TIMEOUT;
        }
	}
	else
	{
		if (!firstDynamicPacketRecieved)
		{
			do
			{
				//std::cout << "waiting for packet..." << std::endl;
				dataReceived = (mSocket->Recieve(inbuff, sizeof(inbuff))==sizeof(inbuff));
				//if (dataReceived)
					//std::cout << "recieved packet with length " << dataReceived << " bytes" << std::endl;
                if (!dataReceived && mTimeLastPacketRecieved.TimeSinceLastEvent()>initTimeout)
                {
                    cleanupUdp();
					terminateRequested = true;
                    return CUS_ERROR_INIT_TIMEOUT;
                }
                
                if (dataReceived && in->simulationMode == SIM_MODE_INITIALIZE && in->protocolVersion==PROTOCOL_VERSION && in->packetID==MODEL_INPUT_PK)
				{
                    delayPacketSend = true;
				}
            }
			while (!dataReceived );
        }
		else
		{
			do
			{
				dataReceived = (mSocket->Recieve(inbuff, sizeof(inbuff))==sizeof(inbuff));
                if (dataReceived && in->protocolVersion==PROTOCOL_VERSION && in->packetID==MODEL_INPUT_PK && in->simulationMode==SIM_MODE_TERMINATE)
                    break;
			}
			while (dataReceived);
            
            
            if (!dataReceived && mTimeLastPacketRecieved.TimeSinceLastEvent()>timeOut)
            {
                cleanupUdp();
				terminateRequested = true;
                return CUS_ERROR_RUNTIME_TIMEOUT;
            }
		}
	}

	bool isInputPacketValid = in->protocolVersion==PROTOCOL_VERSION && in->packetID==MODEL_INPUT_PK;

    if (isInputPacketValid)
    {
		if (in->simulationMode == SIM_MODE_DYNAMIC)
		{
			firstDynamicPacketRecieved = true;
		}
        else if (in->simulationMode == SIM_MODE_TERMINATE)
        {
            cleanupUdp();
			std::cout << "SCANeR stopped the simulation" << std::endl;
			terminateRequested = true;
            return CUS_STOP_SIMULATION;
        }

        mTimeLastPacketRecieved.Event();
        //treat the input packet
        {
            scanerTime = in->scANeRTime;
			//DATA INPUTS PORTS
			//initial conditions
            *initHeading = in->initHeading;
            *initSpeed = in->initSpeed;
            for (int i=0 ; i<3 ; i++)
                initGroundPos[i] = in->initGroundPos[i];
            for (int i=0 ; i<3 ; i++)
				initGroundNormal[i] = in->initGroundNorm[i];
			//real time simulation data
			*enableCommandOverride = in->isCommandOverride;
			//SCANeR driver inputs
            *steeringWheel = in->steeringWheel;
            *steeringWheelSpeed = in->steeringWheelSpeed;
            *accelerator = in->accelerator;
            *brake = in->brake;
            *clutch = in->clutch;
            *wantedGear = in->wantedGear;
            *gearBoxAutoMode = in->gearBoxAutoMode;
            *shiftUp = in->shiftUp;
            *shiftDown = in->shiftDown;
            *ignitionKey = in->ignitionKey;
            *parkingBrake = in->parkingBrake;
            *fowa = in->fowa;
            *telma = in->telma;
            *indicators = in->indicators;
            *lights = in->lights;
            *rearWiperState = in->rearWiperState;
            *frontWiperState = in->frontWiperState;
            *horn = in->horn;
            *warnings = in->warnings;
            *frontFogLights = in->frontFogLights;
            *rearFogLights = in->rearFogLights;
            *trailerBrake = in->trailerBrake;
            *rVLVState = in->rVLVState;
			*rVLVTarget = in->rVLVTarget;
			*transferChoice = in->transferChoice;
			*lockDiffMode = in->lockDiffMode;
			//environment data
			*rain = in->rain;
			*snow = in->snow;
			*windHeading = in->windHeading;
			*windVelocity = in->windVelocity;
			*temperature = in->temperature;
			for (int i = 0; i < 3; i++)
			{
				externalTorserApplicationPoint[i] = in->externalTorserApplicationPoint[i];
				externalTorserForce[i] = in->externalTorserForce[i];
				externalTorserMoment[i] = in->externalTorserMoment[i];
			}
			//wheels data
            if (in->numberOfContactPoints==4)
            {
                assign(wheelSensor0, (ModelInputWheelPk*)&inbuff[sizeof(ModelInputPk)+0*sizeof(ModelInputWheelPk)]);
                assign(wheelSensor1, (ModelInputWheelPk*)&inbuff[sizeof(ModelInputPk)+1*sizeof(ModelInputWheelPk)]);
                assign(wheelSensor2, (ModelInputWheelPk*)&inbuff[sizeof(ModelInputPk)+2*sizeof(ModelInputWheelPk)]);
                assign(wheelSensor3, (ModelInputWheelPk*)&inbuff[sizeof(ModelInputPk)+3*sizeof(ModelInputWheelPk)]);
			}
			//custom
			for (int i = 0; i<NB_CUSTOM_INTPUT_MAX; i++)
				customVehicleInput[i] = in->customVehicleInput[i];
        }


		if (!delayPacketSend)
		{
			//send the response packet
			bool res = mSocket->Send(&outbuf, sizeof(outbuf));
			if (!res)
				std::cout << "Sending output packet " << packetCount << ": failed"<< std::endl;
			++packetCount;
		}
	}

	return CUS_CONTINUE;
}
