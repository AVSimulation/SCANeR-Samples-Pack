/*!****************************************************************************
 * \project  : SCANeR_API                                                     *
 * \file     : EVAL_LONGITUDINAL_CTRL_SPEED.cpp                 					  *
 * \Brief    : Control the pedals regarding acceleration.		              *
 * \Copyright: OKTAL S.A. all rights reserved                                 *
 ******************************************************************************/
//C/C++ includes
#include <iostream>

//scaner project includes
#include "stk/Unit.h"
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
			Com_setShortData(cabToModelOutput, "RVLVState", 1); // RVLVState = 1 for control in speed
			Com_setDoubleData(cabToModelOutput, "RVLVTarget", stk::convToSI(stk::TUnitKilometrePerHour, 100)); // target speed

			Com_updateOutputs(UT_ShmData);
		}
	}
	Process_Close();
}
//--------------------------------------------------------------