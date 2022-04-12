
#pragma once

//version X.x branch

//The file <cal_module.h> describe the interface with CALLAS, it is specify and provided by Oktal only. DO NOT MODIFY IT.
//The update of this file is included into the new version of CALLAS (SDK directory)
#include "Callas/cal_module.h"

class CallasPlugin
{
public:
	CallasPlugin();
	virtual ~CallasPlugin();

	virtual bool good();

	//returns the number of channels to be recorded in the EG results file
	virtual int GetCustomGraphCount();

	//returns the name and unit (must be SI) of the channel to be recorded in the EG results file
	virtual const char* GetCustomGraphName(int index);
	virtual const char* GetCustomGraphUnit(int index);

	virtual bool GetInitCondition(InitCondition* condition, int conditionsize);

	virtual void Idle();

	// this function description the environnement to the external model ( number of vehicle)
	// THIS FUNCTION MUST BE CALL BEFORE InitVhc !!!
	virtual bool InitCalcul(InfoCalcul* data);

	//this function passes a description of the vehicle on to the external model
	virtual bool InitVhc(int novhc, VhcData* data, int datasize);

	virtual void Start();

	//this function should return "true" when the initialization loop is finnished
	//some examples might be waiting for an external resource to be ready (network, engine bench etc...)
	//if this is not the case, just return "1"
	virtual int GetReady();

	//this function is called when going from the "pause" state to the "dynamic" state
	virtual void Resume();

	//this function should return the period at which the model should work "ideally"
	//NOTE: this period is used as a hint and might not be accuratly reproduced during the run
	//the effective period is passed on to the "OKTALInput()" function
	//SPECIAL CASE: return 0 if you want your model to execute at every Callas step
	virtual double Periode();

	//this function should return a "bitwise or" of the flags representing the functions this model exports
	virtual LONG_LONG ExportedFunctions(int novhc);

	//this function should return the size and a pointer of the array containing the needed input channels
	virtual void ChannelsNeeded(int* NbChannels, CANALEG_INDEX** Channels);

	//this function is called to pass the input to the external model.
	//the input is stored in "Input" in the same order as it was requester in "OKTALChannelsNeeded"
	virtual void Input(int novhc, double* Input);

	//this function is called so that the external model can integrate its state
	//NOTE 1: the "DeltaT" period can change and is not necessarily the same as requested
	//this should be taken into account
	//NOTE 2: "OKTALStep" might be called at a frequency that differs from the input and output functions,
	//this is why the input and output functions should not integrate the external model's state (degrees of freedom)
	//the state should be integrated in the step function only
	//NOTE 3: in some cases (ex. steady-state), DeltaT=0, this should be taken into account
	virtual void Step(double DeltaT);

	virtual double GetTimeSetpoint();

	//this function is called for each exported function
	//return "1" if the output was performed sucessfuly, or "0" if the computation
	//must be aborted
	virtual t_SimCode FunctionOutput(int novhc, LONG_LONG FunctionNumber, int* OutputSize, void* Output);

	//this function is called when the state changes from "dynamic" to "pause"
	virtual void Pause();

	//this function is called at the end of the computation
	virtual void Stop();

	virtual t_SimCode SetErrorMessage(const char* Message, int reserved);

	virtual const char* GetErrorMessage();

	virtual int GetUnReady();

	//this function can return a readable description of the modules state
	virtual const char* GetState();

	//this (optional) function can return a handle to the window to be displayed during the simulation
	virtual int GetWindowHandle();

	bool RQPick(const SPoint3D& pickingPos, RoadQueryVal* out);
public:
	void SetRQPickFunction(RQPickFunction Func, void* rq, int sensor);
private:
	RQPickFunction myPickFunc;
	void* myRq;
	int myRqSensor;
};
