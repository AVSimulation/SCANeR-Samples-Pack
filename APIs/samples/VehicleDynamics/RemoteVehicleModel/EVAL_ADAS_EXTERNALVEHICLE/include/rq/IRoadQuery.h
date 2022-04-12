/****************************************************************************************************

		IRoadQuery.h
		Copyright: (c) Oktal SA. All rights reserved.

		Author:	Julien
		Date:	vendredi 13 octobre 2006

****************************************************************************************************/
#pragma once

#include <vector>

#include "rq/rqstruct.h"

namespace ITN
{
	class Network;
}

//! RoadQuery plugin interface
/*! RoadQuery plugin needs to implement all methods
*/
class IRoadQuery	
{
public:
	virtual ~IRoadQuery() {}

	//! Load the associated files
	/* When this method is called, the plugin must load all needed files.
		 /param databasePathName, the full path of the database (path + filename without extension)
		 /param network, the RND network
		 /param enableRugosity, master switch to completely enable/disable rugosity for all RQ sensors
		 /return true if the loading is ok, false otherwise
	*/
	virtual bool loadDB(const char* databasePathName, ITN::Network* network, bool enableRugosity) = 0;

	//! Initialize a wheel
	/* When this method is called, the plugin initializes a new wheel and returns an unique identifier of the wheel
		 /param enableRugosity, enable rugosity for this sensor, rugosity must also be enabled when loading the database for this option to have effect
		 /return unique identifier of the new wheel
	*/
	virtual int  initWheel(bool enableRugosity) = 0;

	//! Reset the optimisation cache of a wheel 
	/* When this method is called, the plugin reset the status of the wheel, next picking will go through the whole database
		/return false if the wheel identifier is unknown
	*/
	virtual bool resetWheel(const int wheelId){return false;};


	//! Return the number of ground properties (physical material description) in the database
	/* 	 /return the number of ground properties
	*/
	virtual int getGroundPropertiesCount() const = 0;

	//! Return the ground properties (physical material description) associated to this index
	/* When this method is called, the plugin must return a const reference of GroundProperties.
		 /param index of the ground
		 /return a const reference on the corresponding ground properties.
	*/
	virtual const GroundProperties& getGroundProperties(int index) const = 0;
	

	//! Make simple vertical picking at the given coodinates
	/* When this method is called, the plugin must fill the RoadVal structure for the given wheel id and for x and y coordinate of the RoadVal struct.
		 /param wheelId unique identifier of the wheel
		 /param pickingPos X,Y,Z position of sensor above the surface
		 /param out Output structure including groud intersection position and ground type informations.
		 /return true if picking ok
	*/
	virtual bool pick(int wheelId, const stk::Vector3& pickingPos, RoadVal& out) = 0;

	//! Make complex picking for the wheel: cutout is the list of RoadVal intersecting wheel plan and ground
	/* When this method is called, the plugin must fill the list of RoadVal structure for the given wheel id.
		 /param wheelId unique identifier of the wheel
		 /param Wheel Input data of the wheel
		 /param out vector of RoadVal for each utput structure for other fields.
		 /return true if cutout ok
	*/
	virtual bool cutout(int wheelId, const RoadWheelData& Wheel, std::vector<RoadVal>& out)=0;


	//! Cleanup
	/* When this method is called, the plugin must unallocate wheels & database data
		 /return true if ok
	*/
	virtual bool end() = 0;

	//! Name of plugin
	/* When this method is called, the plugin must return his name string
		 /return name of plugin
	*/
	virtual const char* name() = 0;

	//! Version of plugin
	/* When this method is called, the plugin must return his version string
		 /return version of plugin
	*/
	virtual const char* version() = 0;

	//! Description of plugin
	/* When this method is called, the plugin must return his description string
		 /return description of plugin
	*/
	virtual const char*  description() = 0;

	virtual void setSimulationTime(double time) = 0;
};

// Definition of the function pointers
typedef IRoadQuery* (*FCT_createRoadQuery)();
