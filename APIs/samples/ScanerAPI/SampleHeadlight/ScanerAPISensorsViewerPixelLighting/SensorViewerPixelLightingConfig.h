#pragma once

#include "stk/Vector3.h"

#include <string>

class SensorViewerPixelLightingConfig
{
public:

	SensorViewerPixelLightingConfig();
	virtual ~SensorViewerPixelLightingConfig();

	bool load(const std::string& configFileName, const std::string& processName);

private:

	void sendParamNotFoundErrorMessage(const std::string & configFileName, const std::string & parameterName) const;

public:

	/** The ID of the NightTestManager light source to update with the viewer image */
	int myLightSourceID;

	/** The width of the window, should be the same width as the photometry */
	int myImageWidth;

	/** The height of the window, should be the same height as the photometry */
	int myImageHeight;
};
