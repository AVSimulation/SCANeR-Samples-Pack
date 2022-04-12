#pragma once

#include "VehicleDynamics/VehicleUDPPackets.h"

#ifdef WIN32
#ifdef SCANER_CALLAS_API_DLL_EXPORTS // SCANER_CALLAS_API_DLL_EXPORTS
#define DLL_EXPORTS __declspec(dllexport)
#else
#define DLL_EXPORTS __declspec(dllimport)
#endif
#else
#define DLL_EXPORTS
#endif


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//the VehicleModel object, stor a pointer of this type as returned by vehicleModelCreate()
typedef struct VehicleModel VehicleModel;

//vehicleModelCreate(): create a VehicleModel object and return it. The vehicle model needs to be loaded with vehicleModelLoad() befor use and freed with vehicleModelRelease()
DLL_EXPORTS VehicleModel* vehicleModelCreate(const char* groundPath);

//vehicleModelLoad(): load a Callas vehicle model, the path should specify a *.vhc file of the correct Callas version
//returns: 0 is successful, otherwise, an error code
DLL_EXPORTS int vehicleModelLoad(VehicleModel* vehicle, char* path);

//vehicleModelGetWheelNumber get the number of wheel associated to the vehicle. It's necessary to load the vehicle with "vehicleModelLoad()" before using this function;
DLL_EXPORTS int vehicleModelGetWheelNumber(VehicleModel* vehicle);

//vehicleModelGetWheelNumber get the number of electricMotor associated to the vehicle. It's necessary to load the vehicle with "vehicleModelLoad()" before using this function;
DLL_EXPORTS int vehicleModelGetElectricMotorNumber(VehicleModel* vehicle);

//vehicleModelGetWheelNumber get the number of turret associated to the vehicle. It's necessary to load the vehicle with "vehicleModelLoad()" before using this function;
DLL_EXPORTS int vehicleModelGetTurretNumber(VehicleModel* vehicle);

//vehicleModelInit(): initialize the vehicle model at a given position, heading and speed as specified in the initialData structure. The vehicle model must be created and loaded before this function can be called
//Instanciation du modèle, initialisation du modèle à la position indiqué dans initialData, customOut est une liste de canaux EG à exporter sur les CustomOut, valeur de retour: un handle opaque sur l'objet vehicle
DLL_EXPORTS int vehicleModelInit(VehicleModel* vehicle, unsigned long long* customOut,\
													int customOutSize, ModelInputPk* initialData); 

//vehicleModelSetInputsTurret(): set the turrets inputs to the vehicle model
DLL_EXPORTS void vehicleModelSetInputsTurret(VehicleModel* vehicle, int turretIndex, ModelInputTurretPk* input);

//vehicleModelSetInputs(): set the inputs to the vehicle model
DLL_EXPORTS void vehicleModelSetInputs(VehicleModel* vehicle, ModelInputPk* inputs, ModelInputWheelPk* wheels);

//vehicleModelStep(): step the timeof the vehicle model by deltatime increment
DLL_EXPORTS int vehicleModelStep(VehicleModel* vehicle, double deltatime);

//vehicleModelGetOuputs(): get the current state of the vehicle
DLL_EXPORTS void vehicleModelGetOuputs(VehicleModel* vehicle, ModelOutputPk* outputs,\
									ModelOutputWheelPk* wheels, ModelOutputElectricMotorPk* electricMotors);

//vehicleModelGetOutputsTurret(): get the current state of the turret vehicle
DLL_EXPORTS void vehicleModelGetOutputsTurret(VehicleModel* vehicle, int turretIndex, ModelOutputTurretPk* input);

//vehicleModelRelease(): all vehicles allocated by vehicleModelCreate() must be freed by this function after use
DLL_EXPORTS void vehicleModelRelease(VehicleModel* vehicle);

//vehicleModelGetErrorMessage() : get the error message and the error code
DLL_EXPORTS void vehicleModelGetErrorMessage(VehicleModel* vehicle, int* errCode, char* errMsg, int msgSize);

#ifdef __cplusplus
}
#endif //__cplusplus