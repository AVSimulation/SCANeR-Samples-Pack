CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

PROJECT(SCANeRstudioSDK)

IF(NOT WIN32)
	IF (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckLSBTypes.cmake)
		INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CheckLSBTypes.cmake)
	ENDIF()
ENDIF(NOT WIN32)

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

IF (NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    message(STATUS "No Build type: switch to Release")
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

string(TIMESTAMP SCANER_YEAR "%Y")

IF(WIN32)
	SET(BINARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/bin/x64/vs2019)
	SET(LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/vs2019)
	SET(SCANER_API_LIB SCANeR_API_C)
ELSE(WIN32)
	SET(BINARY_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/../data/SAMPLE_COMPUTE_HPC/bin/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE})
	SET(LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE})

	SET(SCANER_API_LIB SCANeR_API_C.2022)
	ADD_DEFINITIONS(-DLINUX)
	ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64)
	SET(CMAKE_CXX_FLAGS "-O3 -std=c++11 -Wno-deprecated")
ENDIF(WIN32)

#### ROS
IF(NOT WIN32)
	find_library(ROSCPP_LIBRARY NAMES roscpp)
	get_filename_component(ROSCPP_DIR ${ROSCPP_LIBRARY} DIRECTORY)
	set(ROS_INCLUDE_DIR "${ROSCPP_DIR}/../include")
ENDIF(NOT WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_DIR})


include_directories(${CMAKE_SOURCE_DIR}/include)
IF(WIN32)
	link_directories(${LIBRARY_DIR} 
					${BINARY_DIR}
					${LIBRARY_DIR}/external)
ELSE(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/lib/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE} 
					${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib 
					${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib/external)
	
	# VRX SPECIFIC to link with right libstdc++ (CentOS 7 only)
	IF (${LSB_DISTRIBUTOR_ID} STREQUAL "centos" AND ${LSB_RELEASE} STREQUAL "7")
	        IF(EXISTS ${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib/external/libstdc++.so.6 AND NOT EXISTS ${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib/external/libstdc++.so)
	                        execute_process(
	                        COMMAND ${CMAKE_COMMAND}
	                        -E create_symlink
	                        "${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib/external/libstdc++.so.6"
	                        "${CMAKE_SOURCE_DIR}/../bin/Linux/${LSB_DISTRIBUTOR_ID}/${LSB_RELEASE}/lib/external/libstdc++.so")
	        ENDIF()
	ENDIF()
ENDIF(WIN32)

ADD_SUBDIRECTORY(samples)

