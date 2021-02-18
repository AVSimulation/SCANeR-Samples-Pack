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
    # write access to Shared Memory for longitudinal control
    cabToModelOutput = Com_declareOutputData('Shm/ModelCabin/CabToModel');

    while status != PS_DEAD:
        # Process manager Run 
        Process_Wait()
        Process_Run()
        
        #Process manager State
        old_status = status
        status = Process_GetState()
        
        if status == PS_RUNNING:
            Com_setShortData(cabToModelOutput, "RVLVState", 1) # RVLVState = 1 for control in speed
            Com_setDoubleData(cabToModelOutput, "RVLVTarget", 27) # target speed in m/s

        if Com_updateOutputs(UT_ShmData) == 0: #flush the corrective message
            print 'Update Shm outputs failed...'
            
except KeyboardInterrupt:
    print 'Bye bye'
    Process_Close()