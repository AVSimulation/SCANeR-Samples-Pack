#!*****************************************************************************
#* \project  : SCANeR_API                                                     *
#* \file     : EVAL_LONGITUDINAL_CTRL.py                 					  *
#* \Brief    : Radar sensor, targets detection with SCANeR API.	              *
#* \Copyright: OKTAL S.A. all rights reserved                                 *
# *****************************************************************************/
#!/usr/bin/python
import os
import inspect
from time import sleep
this_file = inspect.currentframe().f_code.co_filename
this_dir = os.path.dirname(this_file)
# to find scaner_api dll
if (os.name == 'nt'):
    os.chdir(os.path.abspath(os.environ['STUDIO_PATH']+'./SCANeRstudio_1.9/APIs/bin/x64/vs2013'))

from scaner import *

parser = ScanerApiOption()
(options, args) = parser.parse_args()
Process_InitParams(options.process_name, options.configuration, ctypes.c_float(options.frequency))

status = PS_DAEMON

try:
    # read access to radar and ExportChannel
    radar_300000 = Com_declareInputData('Network/ISensor/SensorTargets', 300000);
    EC_1000 = Com_declareInputData('Network/IUser/ExportChannel', 1000);
    # write access to Shared Memory for longitudinal control
    CabToModelCorrective_0 = Com_declareOutputData('Shm/ModelCabin/CabToModelCorrective', 0);

    distanceToCollision = -1;
    while status != PS_DEAD:
        # Process manager Run 
        Process_Wait()
        Process_Run()
        
        #Process manager State
        old_status = status
        status = Process_GetState()
        TimeOfUpdate = Process_GetTime()
        
        if status == PS_RUNNING:
            if Com_updateInputs(UT_NetworkData) == 0:
                print 'Update Network inputs failed...'
            targetsCount = Com_getShortData(radar_300000, "targetsArrayCount")

            if targetsCount > 0:
				distanceToCollisionTmp = "targetsArray[%d]/distanceToCollision" % (Com_getShortData(radar_300000, "nearestTarget"))
				distanceToCollision = Com_getFloatData(radar_300000, distanceToCollisionTmp);

            if distanceToCollision != -1:
				if distanceToCollision < Com_getFloatData(EC_1000, "val"): #export channel value used to define the distanceToCollision
					#add brake assistance
					Com_setDoubleData(CabToModelCorrective_0, "BrakeAdditive", 400);
					Com_setDoubleData(CabToModelCorrective_0, "BrakeMultiplicative", 0);
					Com_setDoubleData(CabToModelCorrective_0, "TimeOfUpdate", TimeOfUpdate);
					if Com_updateOutputs(UT_ShmData) == 0: #flush the corrective message
						print 'Update Shm outputs failed...'
				distanceToCollision = -1;
            
except KeyboardInterrupt:
    print 'Bye bye'
    Process_Close()