#!/usr/bin/python
import ctypes
import sys
import os
from optparse import OptionParser
import inspect
from typing import List, NewType

# to find scaner_api dll
if (os.name == 'nt'):
    this_file = inspect.currentframe().f_code.co_filename
    this_dir = os.path.dirname(this_file)
    cur_dir = os.getcwd()
    api_path = os.path.abspath(os.environ['STUDIO_PATH']+'./SCANeRstudio_2023/APIs/bin/x64/vs2019')
    if os.path.exists(api_path):
        os.chdir(api_path)
    scaner_api = ctypes.CDLL(os.environ['STUDIO_PATH']+'/SCANeRstudio_2023/APIs/bin/x64/vs2019/SCANeR_API_C.2023.dll')
    if os.path.exists(api_path):
        os.chdir(cur_dir)
else:
    scaner_api = ctypes.CDLL('libSCANeR_API_C.2023.so')

#structures first
class DataInterface(ctypes.Structure):
    pass

class FieldInfo(ctypes.Structure):
    _fields_ = [("_name", ctypes.c_char * 256),
                ("_type_name", ctypes.c_char * 256)]
    @property
    def name(self):
        return self._name.decode('utf-8')

    @property
    def type_name(self):
        return self._type_name.decode('utf-8')

class Position(ctypes.Structure):
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double),
                ("z", ctypes.c_double)]
    def __str__(self):
        return "(" + str(self.x) + " " + str(self.y) + " " + str(self.z) + ")"
                
class Vehicle(ctypes.Structure):
    _fields_ = [("id", ctypes.c_int),
                ("_vehicleName", ctypes.c_char * 256),
                ("_modelName", ctypes.c_char * 256),
                ("type", ctypes.c_int),
                ("behaviour", ctypes.c_int),
                ("state", ctypes.c_int),
                ("initPosition", Position),
                ("heading", ctypes.c_double)]

    @property
    def vehicleName(self):
        return self._vehicleName.decode('utf-8')
    @property
    def modelName(self):
        return self._modelName.decode('utf-8')
    
    @property
    def name(self):
        return self.vehicleName

    @property
    def model_name(self):
        return self.modelName

    @property
    def init_position(self):
        return self.initPosition
                
    def __str__(self):
        return "id: {0}\nname: {1}\ntype: {2}\nbehaviour: {3}\nstate: {4}\n"\
                "initPosition: {5}\n"\
                "heading: {6}".format(self.id, self.vehicleName, Vehicle.get_type_str(self.type), Vehicle.get_behaviour_str(self.behaviour), Vehicle.get_state_str(self.state), self.initPosition, self.heading)
    
    @staticmethod
    def get_type_str(type):
        if type == CAR:
            return "CAR"
        if type == TRACTOR:
            return "TRACTOR"
        if type == SEMI_TRAILER:
            return "SEMI_TRAILER"
        if type == TRAILER:
            return "TRAILER"
        if type == CAR:
            return "CAR"
        if type == BUS:
            return "BUS"
        if type == MOTORBIKE:
            return "MOTORBIKE"
        if type == BICYCLE:
            return "BICYCLE"
        if type == PEDESTRIAN:
            return "PEDESTRIAN"
        if type == STATIC_OBJECT:
            return "STATIC_OBJECT"
        if type == TRAM:
            return "TRAM"
        if type == TRAIN:
            return "TRAIN"
        if type == UNKNOWN_TYPE:
            return "UNKNOWN_TYPE"
        if type == ALIVEBEING:
            return "ALIVEBEING"
            
    @staticmethod
    def get_behaviour_str(behaviour):
        if behaviour == EXTERNAL:
            return "EXTERNAL"
        if behaviour == AUTONOMOUS:
            return "AUTONOMOUS"
        if behaviour == INTERACTIVE:
            return "INTERACTIVE"
        if behaviour == ANIMATED:
            return "ANIMATED"
        if behaviour == VB_UNKNONW:
            return "VB_UNKNONW"
    
    @staticmethod
    def get_state_str(state):
        if state == V_GHOST:
            return "V_GHOST"
        if state == V_VISIBLE:
            return "V_VISIBLE"
        if state == V_ALIVE:
            return "V_ALIVE"
        if state == V_UNKNOWN:
            return "V_UNKNOWN"

class Object(ctypes.Structure):
    _fields_ = [("id", ctypes.c_int),
                ("_name", ctypes.c_char * 256),
                ("mass", ctypes.c_double),
                ("_static_object", ctypes.c_char),
                ("state", ctypes.c_int),
                ("init_position", Position),
                ("heading", ctypes.c_double),
                ("_heighmap", ctypes.c_char * 256),
                ("_has_heighmap", ctypes.c_byte),
                ("scale", Position),
                ("friction", ctypes.c_double),
                ("rolling_frition", ctypes.c_double),
                ]

    @property
    def name(self):
        return self._name.decode('utf-8')

    @property
    def static_object(self):
        return bool(self._static_object)

    @property
    def heighmap(self):
        return self._heighmap.decode('utf-8')

    @property
    def has_heighmap(self):
        return bool(self._has_heighmap)
    
    def __str__(self):
        return "id: {p.id} \n"\
                "name: {p.name} \n"\
                "mass: {p.mass} \n"\
                "static_object: {p.static_object} \n"\
                "state: {p.state} \n"\
                "init_position: {p.init_position} \n"\
                "heading: {p.heading} \n"\
                "heighmap: {p.heighmap} \n"\
                "has_heighmap: {p.has_heighmap} \n"\
                "scale: {p.scale} \n"\
                "friction: {p.friction} \n"\
                "rolling_frition: {p.rolling_frition} \n".format(p=self)


class  InitialConditions(ctypes.Structure):
    _fields_ = [("_scenario_name", ctypes.c_char * 256), 
            ("_terrain_name", ctypes.c_char * 256),
            ("vehicles_count", ctypes.c_int),
            ("objects_count", ctypes.c_int)]

    @property
    def scenario_name(self):
        return self._scenario_name.decode('utf-8')
    @property
    def terrain_name(self):
        return self._terrain_name.decode('utf-8')

    def vehicles(self, event) -> List[Vehicle]:
        vehicles_list = []
        for i in range(self.vehicles_count):
            vehicles_list.append(Com_getInitConditionsVehicle(event.c_event, i))
        return vehicles_list

    def objects(self, event) -> List[Object]:
        vehicles_list = []
        for i in range(self.objects_count):
            vehicles_list.append(Com_getInitConditionsObject(event.c_event, i))
        return vehicles_list

            
    def __str__(self):
        static_str = "scenario: {0}\n"\
                "terrain: {1}\n"\
                "vehicle count: {2}\n"\
                "objects_count: {3}".format(self.scenario_name, self.terrain_name, self.vehicles_count, self.objects_count)
            
        return static_str

class APIProcessInfo(ctypes.Structure):
    MAX_PROCNAME_SIZE=255
    MAX_HOSTNAME_SIZE=255
    _fields_ = [("state", ctypes.c_int),
                ("_name", ctypes.c_char*MAX_PROCNAME_SIZE),
                ("frequency", ctypes.c_float),
                ("desiredFrequency", ctypes.c_float),
                ("_hostname", ctypes.c_char*MAX_HOSTNAME_SIZE)]
    @property
    def desired_frequency(self):
        return self.desiredFrequency
    @property
    def name(self):
        return self._name.decode('utf-8')
    @property
    def hostname(self):
        return self._hostname.decode('utf-8')
    
#functions
scaner_api.Process_InitParams.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_float]
scaner_api.Process_GetId.restype = ctypes.c_int
scaner_api.Process_GetTime.restype = ctypes.c_double
scaner_api.Process_GetRecordDir.restype = ctypes.c_char_p

scaner_api.Com_declareInputData.restype = ctypes.c_void_p
scaner_api.Com_declareOutputData.restype = ctypes.c_void_p
scaner_api.Com_releaseInterface.argtypes = [ctypes.c_void_p]
scaner_api.Com_validateStateEvent.argtypes = [ctypes.c_void_p]
scaner_api.Com_getLongData.argtypes = [ctypes.c_void_p]
scaner_api.Com_getLongData.restype = ctypes.c_int
scaner_api.Com_getShortData.argtypes = [ctypes.c_void_p]
scaner_api.Com_getShortData.restype = ctypes.c_short
scaner_api.Com_getCharData.argtypes = [ctypes.c_void_p]
scaner_api.Com_getCharData.restype = ctypes.c_byte
scaner_api.Com_getFloatData.argtypes = [ctypes.c_void_p]
scaner_api.Com_getFloatData.restype = ctypes.c_float
scaner_api.Com_getDoubleData.argtypes = [ctypes.c_void_p]
scaner_api.Com_getDoubleData.restype = ctypes.c_double
scaner_api.Com_getStringData.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
scaner_api.Com_getStringData.restype = ctypes.c_char_p
scaner_api.Com_getNextEvent.restype = ctypes.c_void_p
scaner_api.Com_getMessageEventDataStringId.argtypes = [ctypes.c_void_p]
scaner_api.Com_getMessageEventDataStringId.restype = ctypes.c_char_p
scaner_api.Com_getInitConditions.restype = ctypes.POINTER(InitialConditions)
scaner_api.Com_getInitConditions.argtypes = [ctypes.c_void_p]
scaner_api.Com_getFieldNumber.argtypes = [ctypes.c_void_p]
scaner_api.Com_getFieldNumber.restype = ctypes.c_int
scaner_api.Com_getFieldInfoArray.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
scaner_api.Com_getFieldInfoArray.restype = ctypes.c_int

scaner_api.Com_getTypeEvent.argtypes = [ctypes.c_void_p]
scaner_api.Com_getStateEventType.argtypes = [ctypes.c_void_p]
scaner_api.Com_getMessageEventDataInterface.argtypes = [ctypes.c_void_p]
scaner_api.Com_getMessageEventDataInterface.restype = ctypes.c_void_p
scaner_api.Com_getInitConditionsObject.argtypes = [ctypes.c_void_p, ctypes.c_int]
scaner_api.Com_getInitConditionsObject.restype = ctypes.POINTER(Object)
scaner_api.Com_getInitConditionsVehicle.argtypes = [ctypes.c_void_p, ctypes.c_int]
scaner_api.Com_getInitConditionsVehicle.restype = ctypes.POINTER(Vehicle)

scaner_api.Com_setShortData.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_short]
scaner_api.Com_setLongData.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_long]
scaner_api.Com_setCharData.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_byte]
scaner_api.Com_setFloatData.argtypes =  [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_float]
scaner_api.Com_setDoubleData.argtypes =  [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_double]
scaner_api.Com_setStringData.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]

scaner_api.Utils_getPath.argtypes = [ctypes.c_char_p]
scaner_api.Utils_getPath.restype = ctypes.c_void_p
scaner_api.Utils_releaseChar.argtypes = [ctypes.c_void_p]

scaner_api.Utils_getMultiplePath.argtypes = [ctypes.c_char_p]
scaner_api.Utils_getMultiplePath.restype = ctypes.POINTER(ctypes.c_char_p)
scaner_api.Utils_releaseCharArray.argtypes = [ctypes.POINTER(ctypes.c_char_p)]

scaner_api.Simulation_InitParams.argtypes = [ctypes.c_char_p, ctypes.c_float]
scaner_api.Simulation_Launch.restype = ctypes.c_byte
scaner_api.Simulation_LoadScenario.restype = ctypes.c_byte
scaner_api.Simulation_Play.restype = ctypes.c_byte
scaner_api.Simulation_Pause.restype = ctypes.c_byte
scaner_api.Simulation_UnLoad.restype = ctypes.c_byte
scaner_api.Simulation_Stop.restype = ctypes.c_byte
scaner_api.Simulation_KillAllProcesses.restype = ctypes.c_byte
scaner_api.Simulation_AllProcessesOk.restype = ctypes.c_byte
scaner_api.Simulation_WaitForState.restype = ctypes.c_byte
scaner_api.Simulation_StartProcess.restype = ctypes.c_byte
scaner_api.Simulation_GetProcessInfo.restype = ctypes.c_byte
scaner_api.Simulation_IsProcessAutoLaunched.restype = ctypes.c_byte
scaner_api.Simulation_Shutdown.restype = ctypes.c_byte
scaner_api.Simulation_setVarEnv.restype = ctypes.c_byte

#fake type for convinience
EventC = NewType("EventC", ctypes.c_void_p)
DatainterfaceC = NewType("DatainterfaceC", ctypes.c_void_p)

def Process_InitParams(procName: str, configName: str, frequency: float) -> int:
    return scaner_api.Process_InitParams(procName.encode('utf-8'), configName.encode('utf-8'), frequency)

Process_Run = scaner_api.Process_Run
Process_Wait = scaner_api.Process_Wait
Process_GetState = scaner_api.Process_GetState
Process_Close = scaner_api.Process_Close
Process_GetId = scaner_api.Process_GetId
Process_GetTime = scaner_api.Process_GetTime

def Process_OutputLevel(msg: str, level: int) -> None:
    return scaner_api.Process_OutputLevel(msg.encode('utf-8'), level)

def Process_GetRecordDir() -> str:
    return scaner_api.Process_GetRecordDir().decode('utf-8')

def Com_registerEvent(eventId: str, index: int = -1) -> None:
    return scaner_api.Com_registerEvent(eventId.encode('utf-8'), index)

Com_getTypeEvent = scaner_api.Com_getTypeEvent
Com_getStateEventType = scaner_api.Com_getStateEventType
Com_validateStateEvent = scaner_api.Com_validateStateEvent
Com_getNextEvent = scaner_api.Com_getNextEvent

Com_getMessageEventDataInterface = scaner_api.Com_getMessageEventDataInterface

def Com_getMessageEventDataStringId(event: EventC) -> str:
    return scaner_api.Com_getMessageEventDataStringId(event).decode('utf-8')

def Com_declareInputData(dataIdString: str, index: int) -> DatainterfaceC:
    return scaner_api.Com_declareInputData(dataIdString.encode('utf-8'), index)

def Com_declareOutputData(dataIdString: str, index: int) -> DatainterfaceC:
    return scaner_api.Com_declareOutputData(dataIdString.encode('utf-8'), index)

Com_releaseInterface = scaner_api.Com_releaseInterface
Com_updateInputs = scaner_api.Com_updateInputs
Com_updateOutputs = scaner_api.Com_updateOutputs

def Com_getShortData(dataInterface: DatainterfaceC, fieldName: str) -> int:
    return scaner_api.Com_getShortData(dataInterface, fieldName.encode('utf-8'))

def Com_getCharData(dataInterface: DatainterfaceC, fieldName: str) -> int:
    return scaner_api.Com_getCharData(dataInterface, fieldName.encode('utf-8'))

def Com_getFloatData(dataInterface: DatainterfaceC, fieldName: str) -> float:
    return scaner_api.Com_getFloatData(dataInterface, fieldName.encode('utf-8'))

def Com_getDoubleData(dataInterface: DatainterfaceC, fieldName: str) -> float:
    return scaner_api.Com_getDoubleData(dataInterface, fieldName.encode('utf-8'))

def Com_getLongData(dataInterface: DatainterfaceC, fieldName: str) -> int:
    return scaner_api.Com_getLongData(dataInterface, fieldName.encode('utf-8'))

def Com_getStringData(dataInterface: DatainterfaceC, fieldName: str) -> str:
    return scaner_api.Com_getStringData(dataInterface, fieldName.encode('utf-8')).value.decode('utf-8')

def Com_setShortData(dataInterface: DatainterfaceC, fieldName: str, val: int) -> bool:
    return scaner_api.Com_setShortData(dataInterface, fieldName.encode('utf-8'), val)

def Com_setCharData(dataInterface: DatainterfaceC, fieldName: str, val: int) -> bool:
    return scaner_api.Com_setCharData(dataInterface, fieldName.encode('utf-8'), val)

def Com_setFloatData(dataInterface: DatainterfaceC, fieldName: str, val: float) -> bool:
    return scaner_api.Com_setFloatData(dataInterface, fieldName.encode('utf-8'), val)

def Com_setDoubleData(dataInterface: DatainterfaceC, fieldName: str, val: float) -> bool:
    return scaner_api.Com_setDoubleData(dataInterface, fieldName.encode('utf-8'), val)

def Com_setStringData(dataInterface: DatainterfaceC, fieldName: str, val: str) -> bool:
    return scaner_api.Com_setStringData(dataInterface, fieldName.encode('utf-8'), val)

def Com_setLongData(dataInterface: DatainterfaceC, fieldName: str, val: int) -> bool:
    return scaner_api.Com_setLongData(dataInterface, fieldName.encode('utf-8'), val)

Com_getFieldInfoArray = scaner_api.Com_getFieldInfoArray
Com_getFieldNumber = scaner_api.Com_getFieldNumber

def Com_getInitConditions(event):
    return scaner_api.Com_getInitConditions(event).contents
def Com_getInitConditionsVehicle(event, index):
    return scaner_api.Com_getInitConditionsVehicle(event, index).contents
def Com_getInitConditionsObject(event, index):
    return scaner_api.Com_getInitConditionsObject(event, index).contents

def Utils_getPath(fileScanerPath: str) -> str:
    ptr_c_str = scaner_api.Utils_getPath(fileScanerPath.encode('utf-8'))
    ret_val = ctypes.cast(ptr_c_str, ctypes.c_char_p).value.decode('utf-8')
    scaner_api.Utils_releaseChar(ptr_c_str)
    return ret_val

def Utils_getMultiplePath(fileScanerPath: str) -> List[str]:
    list_str_c = scaner_api.Utils_getMultiplePath(fileScanerPath.encode('utf-8'))
    ret = []
    i = 0
    while list_str_c[i]:
        ret.append(list_str_c[i].decode('utf-8'))
        i += 1
    scaner_api.Utils_releaseCharArray(list_str_c)
    return ret

def Simulation_InitParams(config_name: str, frequency: float) -> int:
    return scaner_api.Simulation_InitParams(config_name.encode('utf-8'), frequency)
#Simulation_Close = scaner_api.Simulation_Close

Simulation_Launch = scaner_api.Simulation_Launch

def Simulation_LoadScenario(timeoutms: int, scenario_name: str) -> bool:
    return scaner_api.Simulation_LoadScenario(timeoutms, scenario_name.encode('utf-8'))

Simulation_Play = scaner_api.Simulation_Play
Simulation_Pause = scaner_api.Simulation_Pause
Simulation_UnLoad = scaner_api.Simulation_UnLoad
Simulation_Stop = scaner_api.Simulation_Stop

Simulation_KillAllProcesses = scaner_api.Simulation_KillAllProcesses
Simulation_AllProcessesOk = scaner_api.Simulation_AllProcessesOk

def Simulation_WaitForState(modules: str, state: int, timeoutms: int) -> bool:
    return scaner_api.Simulation_WaitForState(modules.encode('utf-8'), state, timeoutms)

def Simulation_StartProcess(module_name: str, timeoutms: int) -> bool:
    return scaner_api.Simulation_StartProcess(module_name.encode('utf-8'), timeoutms)

Simulation_KillProcess = scaner_api.Simulation_KillProcess

def Simulation_KillProcesses(module_name: str, timeoutms: int) -> None:
    return scaner_api.Simulation_KillProcesses(module_name.encode('utf-8'), timeoutms)

Simulation_UpdateProcessInfo = scaner_api.Simulation_UpdateProcessInfo
Simulation_GetProcessNumber = scaner_api.Simulation_getProcessNumber

def Simulation_GetAllProcessInfo() -> List[APIProcessInfo]:
    process_infos = (APIProcessInfo*Simulation_GetProcessNumber())()
    scaner_api.Simulation_getAllProcessInfo(process_infos)
    return process_infos

Simulation_getProcessNumber = scaner_api.Simulation_getProcessNumber
Simulation_getAllProcessInfo = scaner_api.Simulation_getAllProcessInfo
Simulation_GetProcessInfo = scaner_api.Simulation_GetProcessInfo

def Simulation_GetIdFromName(module_name: str) -> int:
    return scaner_api.Simulation_GetIdFromName(module_name.encode('utf-8'))

Simulation_IsProcessAutoLaunched = scaner_api.Simulation_IsProcessAutoLaunched
Simulation_Shutdown = scaner_api.Simulation_Shutdown
Simulation_setVarEnv = scaner_api.Simulation_setVarEnv

def Simulation_ChangeConfig(config_name: str) -> None:
    return scaner_api.Simulation_ChangeConfig(config_name.encode('utf-8'))

def Simulation_SetVarEnv(var_env: str) -> None:
    return scaner_api.Simulation_setVarEnv(var_env.encode('utf-8'))

#enum
(PS_DEAD,
PS_DAEMON,
PS_LOADED,
PS_PAUSED,
PS_READY,
PS_RUNNING) = list(map(int, range(6)))

def state_string(state):
    """return the input state as it's string representation"""
    if state == PS_DEAD:
        return "DEAD"
    if state == PS_DAEMON:
        return "DAEMON"
    if state == PS_LOADED:
        return "LOADED"
    if state == PS_PAUSED:
        return "PAUSED"
    if state == PS_READY:
        return "READY"
    if state == PS_RUNNING:
        return "RUNNING"

OL_Notify = 1
OL_Debug = 2
OL_Warning = 3
OL_Err = 4

(UT_Unknown, UT_AllData, UT_NetworkData, UT_ShmData) = list(map(int, range(4)))

(ET_message, ET_state, ET_unknown) = list(map(int, range(3)))

(ST_Unknown, ST_Load, ST_Start, ST_Init, ST_Go, ST_Pause, ST_Stop, ST_Unload, ST_Kill) = list(map(int, range(9)))

(V_GHOST, V_VISIBLE, V_ALIVE, V_UNKNOWN) = list(map(int, range(4)))

UNKNOWN_TYPE=0
RIGID=1
TRACTOR=2
SEMI_TRAILER=3
TRAILER=4
CAR=5
BUS=6
MOTORBIKE=7
BICYCLE=8
PEDESTRIAN=9
STATIC_OBJECT=10
TRAM=11
TRAIN=12
ALIVEBEING=13
CNT_VEHICLETYPE = 14

EXTERNAL=0
AUTONOMOUS=1
INTERACTIVE=2
ANIMATED=3
VB_UNKNONW=4

#APIShutdownType
ST_POWEROFF  = 0 
ST_REBOOT	  = 1
ST_SHUTDOWN  = 2
ST_STANDBY	  = 3

#OState
O_GHOST = 0
O_VISIBLE = 1
O_ALIVE = 2
O_UNKNOWN = 3

# event more pythonic test
class Events:
    """
    python iterable on scaner api events
    """
    def __iter__(self):
        return EventsIterator()
        
class Event:
    def __init__(self):
        self.c_event = Com_getNextEvent()
        if self.c_event:
            self.type = Com_getTypeEvent(self.c_event)
        
    def __bool__(self):
        return self.c_event != None
        
    def state(self):
        if self.type == ET_state:
            return Com_getStateEventType(self.c_event)
        else:
            return None
        
    def validate(self):
        if self.type == ET_state:
            Com_validateStateEvent(self.c_event)
        
    def data_interface(self):
        return Com_getMessageEventDataInterface(self.c_event)
        
    def message_name(self):
        return Com_getMessageEventDataStringId(self.c_event)
        
    def get_initial_conditions(self) -> InitialConditions:
        return Com_getInitConditions(self.c_event)
    
class EventsIterator:
    """
    Iterator on scaner api events
    """
    def __next__(self):
        event = Event()
        if not event:
            raise StopIteration
        return event

class ScanerApiOption(OptionParser):
    def __init__(self, default_name = 'PYTHON', default_config = 'NL_1.1', default_frequency = 20, default_config_file="", usage=""):
        OptionParser.__init__(self, usage)
        self.add_option("-p", "--process_name", 
                          dest="process_name",
                          type="string", default=default_name,
                          help="Process name")
        self.add_option("-c", "--configuration",
                          dest="configuration", default=default_config,
                          help="Scaner Configuration")
        self.add_option("-f", "--frequency",
                          dest="frequency",
                          type = 'int', default=default_frequency,
                          help="Module frequency")
        self.add_option("--cfg", "--config_file",
                        dest="config_file",
                        type = "string", default=default_config_file,
                        help="Configuration file name")
    def parse_args(self, args=None, values=None):
        if not args:
            args = sys.argv
        try:
            args[args.index('-cfg')] = '--cfg'
            print('-cfg detected')
        except ValueError:
            pass
        return OptionParser.parse_args(self, args, values)
            
                          
def get_main_arg():
    argv = (ctypes.c_char_p * len(sys.argv))()
    for i in range(len(sys.argv)):
        argv[i] = sys.argv[i]
    return argv
    
def print_info_message(data_interface):
    print(get_message_description(data_interface))
    
def get_message_description(data_interface):
    nb_field = Com_getFieldNumber(data_interface)
    if nb_field == 0:
        return ""

    description_string = ""
    field_info_array = (FieldInfo * nb_field)()
    if Com_getFieldInfoArray(data_interface, field_info_array) != 0:
        for i in range(nb_field):
            description_string = description_string + '\t' + field_info_array[i].name + " type of " + field_info_array[i].type_name + '\n'
            
    return description_string

def print_set_itinerary(data_interface):
    id = Com_getShortData(data_interface, 'vhlId')
    print('id ', id)
    add = Com_getCharData(data_interface, 'add')
    print('add ', ord(add))
    directions = Com_getShortData(data_interface, 'directionsCount')
    print('directionsCount ', directions)
    
    for direction in range(directions):
        dir = Com_getCharData(data_interface, 'directions['+str(direction)+']')
        print('directions['+str(direction)+'] ', ord(dir))

def print_path(data_interface):
    id = Com_getShortData(data_interface, 'vhlId')
    print('id ', id)
    directions = Com_getShortData(data_interface, 'directionsCount')
    print('directionsCount ', directions)
    
    for direction in range(directions):
        dir = Com_getCharData(data_interface, 'directions[{}]/direction'.format(direction))
        print('directions[{}]/direction '.format(direction), dir)
        intersection = Com_getLongData(data_interface, 'directions[{}]/intersection'.format(direction))
        print('directions[{}]/intersection '.format(direction), intersection)
        
def print_infra_position(data_interface):
    id = Com_getShortData(data_interface, 'id')
    print('id ', id)
    x = Com_getFloatData(data_interface, 'x')
    y = Com_getFloatData(data_interface, 'y')
    z = Com_getFloatData(data_interface, 'z')
    print('(', x, ' ', y, ' ', z, ')')
    h = Com_getFloatData(data_interface, 'h')
    p = Com_getFloatData(data_interface, 'p')
    r = Com_getFloatData(data_interface, 'r')
    print('(', h, ' ', p, ' ', r, ')')
    
def print_collision(data_interface):
    type = Com_getShortData(data_interface, 'collisionType')
    print('type ', type)
    id1 = Com_getShortData(data_interface, 'id1')
    print('id1 ', id1)
    id2 = Com_getShortData(data_interface, 'id2')
    print('id2 ', id2)
    
    x = Com_getFloatData(data_interface, 'point1_X')
    y = Com_getFloatData(data_interface, 'point1_Y')
    z = Com_getFloatData(data_interface, 'point1_Z')
    print('(', x, ' ', y, ' ', z, ')')
    x = Com_getFloatData(data_interface, 'point2_X')
    y = Com_getFloatData(data_interface, 'point2_Y')
    z = Com_getFloatData(data_interface, 'point2_Z')
    print('(', x, ' ', y, ' ', z, ')')
    x = Com_getFloatData(data_interface, 'force1_X')
    y = Com_getFloatData(data_interface, 'force1_Y')
    z = Com_getFloatData(data_interface, 'force1_Z')
    print('force (', x, ' ', y, ' ', z, ')')
    x = Com_getFloatData(data_interface, 'force2_X')
    y = Com_getFloatData(data_interface, 'force2_Y')
    z = Com_getFloatData(data_interface, 'force2_Z')
    print('force (', x, ' ', y, ' ', z, ')')

def print_trafic_light_update(data_interface):
    id = Com_getShortData(data_interface, 'id')
    stateCount = Com_getCharData(data_interface, 'stateCount')
    print('Road Sign ', str(id))
    for stateIndex in range(ord(stateCount)):
        state = Com_getCharData(data_interface, 'state[{}]'.format(stateIndex))
        print('Light ', stateIndex, ' state ', ord(state))
