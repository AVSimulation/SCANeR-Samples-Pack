/*!****************************************************************************
 * \project  : SCANeR_API                                                     *
 * \file     : EVAL_LONGITUDINAL_CTRL_ACCEL.cpp                 					  *
 * \Brief    : Control the pedals regarding acceleration.		              *
 * \Copyright: OKTAL S.A. all rights reserved                                 *
 ******************************************************************************/
//C/C++ includes
#include <iostream>

//scaner project includes
#include "scanerAPI/scanerAPI_DLL_C.h"
#include "scanerAPI/ScanerAPImessagesShm.h"

int main(int argc, char* argv[])
{
	Process_Init(argc, argv);

	// write access to Shared Memory for longitudinal control
	DataInterface* cabToModelOutput = Com_declareOutputData(SHM_MODELCABIN_CABTOMODEL);

	APIProcessState status = PS_DAEMON;

	while(status != PS_DEAD) // main loop
	{
		Process_Wait(); // synchronization
		Process_Run(); // step
		
		status = Process_GetState();

		if (Process_GetState() == PS_RUNNING) // simulation is running
		{
			double time = Process_GetTime();
			Com_setShortData(cabToModelOutput, "RVLVState", 3); // RVLVState = 3 for control in acceleration
			
			// from 0s to 10s: The vehicle accelerate at 1.1 m/s2
			// from 10s to 20s the vehicle does not accelerate
			// from 20s to the end the vehicle decelerate (brake)
			double targetAccel = 0;
			if (time < 10)
				targetAccel = 1.1;
			else if (time < 20)
				targetAccel = 0;
			else
				targetAccel = -1.1;
			
			Com_setDoubleData(cabToModelOutput, "RVLVTarget", targetAccel); // target acceleration

			Com_updateOutputs(UT_ShmData);
		}
	}
	Process_Close();
}
//--------------------------------------------------------------