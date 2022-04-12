//
// File : rqstruct.h
// Copyright (C) 2000, Renault all rights reserved
// SCANeR II is distributed by OKTAL S.A.
//

/* Autor : F. Fourre              */

#pragma once

#include "stk/Vector3.h"
#include "stk/Mark.h"
#include "ITN/LaneType.h"
#include "ITN/GroundType.h"

#include <string.h>

struct RoadVal
{
	RoadVal() :
		pos(0,0,0),
		norm(0,0,1),
		laneType(ITN::eLanePaved),
		waterHeight(0),
		groundIndex(-1),
		objectId(-1){}

	stk::Vector3 pos;
	stk::Vector3 norm;
	
	ITN::LaneType		laneType;

	float				waterHeight; //in m

	// Ground index. Access the GroundProperties 
	int groundIndex;

	//Id of the object under the wheel
	int objectId;
}; 

struct TerramecanicsGroundModel
{
	// default contructor
	TerramecanicsGroundModel() :
		slipCoefficient(0),
		KcBekker(0),
		KphiBekker(0),
		nBekker(0),
		mGrahn(0),
		rubberGrip(0),
		metalGrip(0) 
		{}

	// data
	float slipCoefficient;
	float KcBekker;
	float KphiBekker;
	float nBekker;
	float mGrahn;
	float rubberGrip;
	float metalGrip;
};

struct FunctionalGroundModel
{
	// default contructor
	FunctionalGroundModel() :
		referenceSinkage(0),
		verticalLoadForSinkage(0),
		contactSurfaceForSinkage(0),
		referenceResistiveForce(0),
		sinkageForForce(0),
		rutWidthForForce(0),
		maxGripNonSkid(0),
		maxGripSkidding(0)
		{}

	// data
	float referenceSinkage;
	float verticalLoadForSinkage;
	float contactSurfaceForSinkage;
	float referenceResistiveForce;
	float sinkageForForce;
	float rutWidthForForce;
	float maxGripNonSkid;
	float maxGripSkidding;
};

struct SoftGroundProperties
{
	//definitions
	enum ModelType { TModelTerramecanics, TModelFunctionnal };

	// default contructor
	SoftGroundProperties() :
		humidity(0),
		volumetricMass(0),
		coneIndex(0),
		cohesion(0),
		frictionAngle(0),
		type(TModelFunctionnal),
		terramecanicsData(),
		functionalData() 
		{}

	// data
	float humidity;
	float volumetricMass;
	float coneIndex;
	float cohesion;
	float frictionAngle;

	ModelType type;
	TerramecanicsGroundModel	terramecanicsData;
	FunctionalGroundModel		functionalData;
};

struct GroundProperties
{
	GroundProperties() :
		grip(1.0f),
		roughnessHeight(0.0f),
		roughnessLength(0.01f),
		roughnessHeightStdDeviation(0.0f),
		roughnessLengthStdDeviation(0.0f),
		groundType(ITN::eGroundAsphalt),
		isSoftGround(false),
		softGroundProperties()
	{
		strncpy(name, "asphalt", sizeof(name)-1);
	}

	char			    name[260];
	float			    grip;
	float				roughnessHeight;
	float				roughnessLength;
	float				roughnessHeightStdDeviation;
	float				roughnessLengthStdDeviation;
	ITN::GroundType		groundType;

	bool isSoftGround;
	SoftGroundProperties softGroundProperties;
};

struct RoadWheelData
{
	stk::Mark pos; //position of the wheel center
	double radius; //radius of the wheel
};

//#define LN_TYPE         {"Normal road","Sidewalk","Ground",\
//	"Obstacle","Parking","Island","Special","Out of surface","Emergency stop area"}
/* 2D surface database... */
#define TTS_LN_TYPE	{"NORMAL_RD","SIDEWALK","GROUND",\
	"OBSTACLE","PARKING","ISLET","SPECIAL_MARKING","OUT_OF_SURFACE","STOP_AREA"}


