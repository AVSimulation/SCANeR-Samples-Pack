#pragma once

#ifdef WIN32
#ifdef CALLAS_RT_UTIL_DLL_EXPORTS // CALLAS_RT_UTIL_DLL_EXPORTS
#define CALLASRT_DLL_EXPORTS __declspec(dllexport)
#else
#define CALLASRT_DLL_EXPORTS __declspec(dllimport)
#endif
#else
#define CALLASRT_DLL_EXPORTS
#endif

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

	CALLASRT_DLL_EXPORTS void getFilePathInModelDir(char* outPathBuffer, int bufferSize,const char* fileName);

	CALLASRT_DLL_EXPORTS int loadcustomChannelPathList(char* customChannelPath, unsigned long long* customOutputs, int* nbCustomOutputs);

	typedef void(*fLogCallBack)(const char* message);
	CALLASRT_DLL_EXPORTS void setLogCallBackFunction(fLogCallBack logCallBack);

	CALLASRT_DLL_EXPORTS void removeLogCallBackFunction();

	CALLASRT_DLL_EXPORTS void getFileExtension(const char* fileName, char* extension); // returns file extension exemple: file.csv -> '.csv'

#ifdef __cplusplus
}
#endif //__cplusplus

