#include "CallasPlugin.h"

 CallasPlugin::CallasPlugin() :
	myPickFunc(0),
	myRq(0),
	myRqSensor(0)
{}

CallasPlugin::~CallasPlugin()
{}
bool CallasPlugin::good() {return true;}
int CallasPlugin::GetCustomGraphCount() {return 0;}
const char* CallasPlugin::GetCustomGraphName(int index) {return 0;}
const char* CallasPlugin::GetCustomGraphUnit(int index) {return 0;}
bool CallasPlugin::GetInitCondition(InitCondition* condition, int conditionsize) {return false;}
void CallasPlugin::Idle() {}
bool CallasPlugin::InitCalcul(InfoCalcul *data) {return true;}
bool CallasPlugin::InitVhc(int novhc, VhcData* data, int datasize) {return true;}
void CallasPlugin::Start() {}
int CallasPlugin::GetReady() {return 1;}
void CallasPlugin::Resume() {}
double CallasPlugin::Periode() {return 0.01;}
LONG_LONG CallasPlugin::ExportedFunctions(int novhc) {return 0;}
void CallasPlugin::ChannelsNeeded(int* NbChannels, CANALEG_INDEX** Channels) {*NbChannels = 0;}
void CallasPlugin::Input(int novhc, double* Input) {}
void CallasPlugin::Step(double DeltaT) {}
double CallasPlugin::GetTimeSetpoint() {return 0;}
t_SimCode CallasPlugin::FunctionOutput(int novhc, LONG_LONG FunctionNumber, int* OutputSize, void* Output) {return TSimOK;}
void CallasPlugin::Pause() {}
void CallasPlugin::Stop() {}
t_SimCode CallasPlugin::SetErrorMessage(const char* Message, int reserved) {	return TSimOK;}
const char* CallasPlugin::GetErrorMessage() { return "";}
int CallasPlugin::GetUnReady() {return 1;}
int CallasPlugin::GetWindowHandle() {return 0;}
const char* CallasPlugin::GetState() {return "NA";}
bool CallasPlugin::RQPick(const SPoint3D& pickingPos, RoadQueryVal* out)
{
	if (myPickFunc==0)
		return false;
	return myPickFunc(myRq, myRqSensor, pickingPos, out)!=0;
}
void CallasPlugin::SetRQPickFunction(RQPickFunction Func, void* rq, int sensor)
{
	myPickFunc = Func;
	myRq = rq;
	myRqSensor = sensor;
}

////////////////////////////////////////////////////////////////////////

void OKTAL_DECL OKTALSetRQPickFunction(void* PrivateStruct, RQPickFunction Func, void* rq, int sensor)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->SetRQPickFunction(Func, rq, sensor);
}

int OKTAL_DECL OKTALGetCustomGraphCount(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetCustomGraphCount();
}

const char* OKTAL_DECL OKTALGetCustomGraphName(void* PrivateStruct, int index)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetCustomGraphName(index);
}

const char* OKTAL_DECL OKTALGetCustomGraphUnit(void* PrivateStruct, int index)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetCustomGraphUnit(index);
}

bool OKTAL_DECL OKTALGetInitCondition(void* PrivateStruct, InitCondition* condition, int conditionsize)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetInitCondition(condition, conditionsize);
}

bool OKTAL_DECL OKTALInitCalcul(void* PrivateStruct, InfoCalcul* data)
{
	CallasPlugin* module = (CallasPlugin*)PrivateStruct;
	return module->InitCalcul(data);
}

void OKTAL_DECL OKTALIdle(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Idle();
}

const char* OKTAL_DECL OKTALGetState(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetState();
}

bool OKTAL_DECL OKTALInitVhc(void* PrivateStruct, int novhc, VhcData* data, int datasize)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->InitVhc(novhc, data, datasize);
}

void OKTAL_DECL OKTALStart(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Start();
}

void OKTAL_DECL OKTALResume(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Resume();

}

int OKTAL_DECL OKTALGetReady(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetReady();
}

double OKTAL_DECL OKTALPeriode(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->Periode();
}

LONG_LONG OKTAL_DECL OKTALExportedFunctions(void* PrivateStruct, int novhc)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->ExportedFunctions(novhc);
}


void OKTAL_DECL OKTALChannelsNeeded(void* PrivateStruct, int* NbChannels, CANALEG_INDEX** Channels)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->ChannelsNeeded(NbChannels, Channels);
}

void OKTAL_DECL OKTALInput(void* PrivateStruct, int novhc, double* Input)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Input(novhc, Input);
}

void OKTAL_DECL OKTALStep(void* PrivateStruct, double DeltaT)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Step(DeltaT);
}

double OKTAL_DECL OKTALGetTimeSetpoint(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetTimeSetpoint();
}

t_SimCode OKTAL_DECL OKTALFunctionOutput(
	void* PrivateStruct,
	int novhc,
	LONG_LONG FunctionNumber,
	int* OutputSize,
	void* Output)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->FunctionOutput(novhc, FunctionNumber, OutputSize, Output);
}

void OKTAL_DECL OKTALPause(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Pause();
}

void OKTAL_DECL OKTALStop(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	module->Stop();
}

t_SimCode OKTAL_DECL OKTALSetErrorMessage(void* PrivateStruct, const char* Message, int reserved)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->SetErrorMessage(Message, reserved);
}

const char* OKTAL_DECL OKTALGetErrorMessage(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetErrorMessage();
}


int OKTAL_DECL OKTALGetUnReady(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetUnReady();
}

void OKTAL_DECL OKTALDeletePrivateStruct(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	delete module;
}

int OKTAL_DECL OKTALGetWindowHandle(void* PrivateStruct)
{
	CallasPlugin* module =(CallasPlugin*)PrivateStruct;
	return module->GetWindowHandle();
}

