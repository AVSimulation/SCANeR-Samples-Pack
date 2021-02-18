#include "SensorViewerPixelLightingConfig.h"

#include "scanerAPI/scanerAPI_DLL_C.h"
#include "stk/FileTools.h"

//#include <iostream>
#include <sstream>


//=============================================================================

SensorViewerPixelLightingConfig::SensorViewerPixelLightingConfig() :
myLightSourceID(0),
myImageWidth(800),
myImageHeight(600)
{
}

//=============================================================================

SensorViewerPixelLightingConfig::~SensorViewerPixelLightingConfig()
{
}

//=============================================================================

bool SensorViewerPixelLightingConfig::load(const std::string& configFileName, const std::string& processName)
{
	std::string configFile("config/");
	configFile += configFileName;

	std::string configFileAbsPath = Utils_getPath(configFile.c_str());
	if (stk::FileExist(configFileAbsPath.c_str()))
	{
		std::istringstream iss;

		//light source ID
		const char* token = Utils_getTokenValueFromSection(configFileAbsPath.c_str(), "lightSourceID", processName.c_str());
		std::string tokenStr(token);
		if (tokenStr.empty())
		{
			sendParamNotFoundErrorMessage(configFileName, "lightSourceID");
			return false;
		}
		iss.str(token);
		iss >> myLightSourceID;
		Utils_releaseChar(token);

		//image width
		token = Utils_getTokenValueFromSection(configFileAbsPath.c_str(), "imageWidth", processName.c_str());
		tokenStr = token;
		if (tokenStr.empty())
		{
			sendParamNotFoundErrorMessage(configFileName, "imageWidth");
			return false;
		}
		iss.clear();
		iss.str(token);
		iss >> myImageWidth;
		Utils_releaseChar(token);

		//image height
		token = Utils_getTokenValueFromSection(configFileAbsPath.c_str(), "imageHeight", processName.c_str());
		tokenStr = token;
		if (tokenStr.empty())
		{
			sendParamNotFoundErrorMessage(configFileName, "imageHeight");
			return false;
		}
		iss.clear();
		iss.str(token);
		iss >> myImageHeight;
		Utils_releaseChar(token);

		return true;
	}

	std::string errorMsg("Could not find ");
	errorMsg += configFileName;
	errorMsg += " configuration file";
	Process_OutputLevel(errorMsg.c_str(), OL_Err);
	return false;
}

//=============================================================================

void SensorViewerPixelLightingConfig::sendParamNotFoundErrorMessage(const std::string & configFileName, const std::string & parameterName) const
{
	std::string errorMsg("Could not find '");
	errorMsg += parameterName;
	errorMsg += "' parameter in ";
	errorMsg += configFileName;
	errorMsg += " configuration file";
	Process_OutputLevel(errorMsg.c_str(), OL_Err);
}
