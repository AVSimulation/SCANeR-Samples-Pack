//
// File : motionStategyInterface.h
// Copyright (C) 2000, AVSimulation all rights reserved

//
// This class is an interface of the Motion Platform Strategy

#pragma once

#include "Motion/MotionStrategyStruct.h"
#include "Motion/MotionComStruct.h"
#include "Motion/MotionComInterface.h"
#include "Motion/MotionInput.h"

class MotionStrategyInterface
{
public:
	virtual ~MotionStrategyInterface(){};

	// This functions contains the motion Platform strategy Algorithm.
	virtual bool compute(
		double simulationTime,
		double deltaT,
		const mc::MotionInput& modelToPlatform, // modelToPlatform structure contains data from dynamic models to motion
		const MotionComOutput& motionPos, // motionPos structure contains feeback data from motion system (from Communication DLL)
		MotionStrategyOutput& out // fill StrategyOutput structure (this structure is passed to Communication DLL).
	)=0;

	virtual void startLogging(const char* dir) {}
	virtual void stopLogging() {}
};

typedef MotionStrategyInterface* (*FCT_createMotionStrategy)(
	const char* configFile, //configuration file for the strategy
	const char* geometryFile, //information about the platform (dimensions...)
	int motionComFeatures //motionComFeatures
);
