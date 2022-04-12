
#pragma once

#if defined(__linux__)
#define declScanerRQAPI
#else
#ifdef SCANERRQ_EXPORTS
#define declScanerRQAPI __declspec(dllexport)
#else 
#define declScanerRQAPI __declspec(dllimport)
#endif
#endif

#ifdef __cplusplus 

extern "C" {
/*opaque pointer to the road query interface*/
struct RoadQueryInterface;
#define SC_CONST const

#else

#define SC_CONST
#define RoadQueryInterface void

#endif

/*structure describing a point of the road query cutout or pick*/
typedef struct
{
	double nx, ny, nz;
	double posx, posy, posz;
	int groundIndex;
	float waterHeight;
} RoadQueryContactStruct;

typedef struct
{
	char name[260];
	float grip;
	float roughnessHeight;
	float roughnessLength;
	float roughnessHeightStdDeviation;
	float roughnessLengthStdDeviation;
	int groundType;
} RoadQueryGroundStruct;

/*initialize the road query interface with a given SCANeR configuration and a RND database name
this must be done before calling any of the other functions*/
declScanerRQAPI RoadQueryInterface* roadQueryLoadDB(SC_CONST char* scanerConfigurationName, SC_CONST char* dbName);

/*get the error message (use this if roadQueryLoadDB returns a result different from 0)*/
declScanerRQAPI SC_CONST char* roadQueryGetErrorMessage(RoadQueryInterface* rqInterface);

/*create a new sensor (rqInterface must be correctly initialized first)
one sould be created for each wheel*/
declScanerRQAPI int roadQueryNewSensor(RoadQueryInterface* rqInterface);

/*get the number of ground properties in the current terrain database*/
declScanerRQAPI int roadQueryGetGroundCount(RoadQueryInterface* rqInterface);

/*get a specific ground property for a given index*/
declScanerRQAPI int roadQueryGetGround(RoadQueryInterface* rqInterface, int i, RoadQueryGroundStruct* ground);

/*pick the ground at the given by the (x y z) coordinates*/
declScanerRQAPI int roadQueryPick(RoadQueryInterface* rqInterface, int sensorNumber,
	double x, double y, double z,
	RoadQueryContactStruct* pick);


/*cutout the ground with the plane defined by the (x y z r p h) frame's z/x plane  coordinates*/
declScanerRQAPI int roadQueryCutout(RoadQueryInterface* rqInterface, int sensorNumber,
	double x, double y, double z, double r, double p, double h, double radius,
	RoadQueryContactStruct* cutout, unsigned int* cutoutSize);

/*free the road query interface, this must be done befor the end of the simulation*/
declScanerRQAPI void roadQueryFree(RoadQueryInterface* rqInterface);

#ifdef __cplusplus 
}
#endif
