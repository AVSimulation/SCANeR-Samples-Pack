<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<sce version="20.23.1" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

  <Scenario>
    <description>-------------------------------------
Scenario:
The EGO vehicle (ID 0) is controlled by a virtual driver (driver commands emulator) with the following instruction: 
- Streering wheel anle 0°.
- Initial speed 50 Km/h.
- From 0 to 30 seconds the speed is constant 50 Km/h.
- The Pedestrian (ID 1) is inactive when the scenario begin.
- When the EGO vehicle goes over the "pedestrianActivation" trigger then the Pedestrian cross the road whitout paying attention to the vehicle.
- An ADAS (developed using the SCANeR API) force the vehicle to brake when the vehicle is a distance of less than 20 meters (by default, this distance can be configured using the dynamic variable initialization).
-------------------------------------
Needed modules:
ACQUISITION, MODELHANDLER, SCENARIO, SENSORS, WALKERTRAFFIC
+
LONGI_PY (or LONGI_C or LONGI_SMLNK).
-------------------------------------
Note:
LONGI_SMLNK is for Co-simulation (run the Simulink model into Matlab/Simulink).
LONGI_PY is the built version of the Python code.
LONGI_C is the built version of the C++ code.
These 3 SCANeR API modules are identical, only one must be executed.</description>
    <name>AEB_EVAL_ADAS_CTRL 33</name>
    <online>1</online>
    <steadystate>0</steadystate>
    <Environment>
      <gravity>9.81</gravity>
      <waterVolumetricMass>1000</waterVolumetricMass>
      <DayTime>
        <dawnTime>21600</dawnTime>
        <day>1</day>
        <duskTime>72000</duskTime>
        <month>6</month>
        <startTime>43200</startTime>
        <year>2000</year>
      </DayTime>
      <Lighting>
        <dynamicLighting>1</dynamicLighting>
        <lightMax>1</lightMax>
        <lightMin>0</lightMin>
      </Lighting>
      <Panorama>
        <file></file>
        <scale>0.00225</scale>
      </Panorama>
      <Weather>
        <airTemperature>293.15</airTemperature>
        <atmosphericPressure>101500</atmosphericPressure>
        <autoComputeFogColor>1</autoComputeFogColor>
        <autoComputeFogDistance>1</autoComputeFogDistance>
        <cloudsLevel>0.2</cloudsLevel>
        <fogColor>0.5 0.5 0.5</fogColor>
        <fogDistance>20000</fogDistance>
        <fogEnable>1</fogEnable>
        <groundTemperature>293.15</groundTemperature>
        <hygrometry>0.5</hygrometry>
        <rainLevel>0</rainLevel>
        <skySaturation>1</skySaturation>
        <snowLevel>0</snowLevel>
        <snowOnRoad>0</snowOnRoad>
        <waterOnRoad>0</waterOnRoad>
      </Weather>
    </Environment>
    <ExternalTraffic>
      <extTrafficConfigFile></extTrafficConfigFile>
      <replication>0</replication>
    </ExternalTraffic>
    <ExternalTrafficConnexion>
      <host></host>
      <port>0</port>
    </ExternalTrafficConnexion>
    <Ground>
      <enableRoughness>0</enableRoughness>
      <infrastructure></infrastructure>
      <isParametric>0</isParametric>
      <name>EVAL_ADAS_2.rnd</name>
      <useSpecificSurfaceForTraffic>0</useSpecificSurfaceForTraffic>
    </Ground>
    <PredefinedRun>
      <type>0</type>
      <TacticalMobility>
        <backupSampleTime>0.1</backupSampleTime>
        <brakePedalPressDelay>2</brakePedalPressDelay>
        <finalDistance>200</finalDistance>
        <gasPedalPressDelay>1</gasPedalPressDelay>
        <maxForceOnBrakePedal>400</maxForceOnBrakePedal>
        <maxPosGasPedal>1</maxPosGasPedal>
      </TacticalMobility>
      <StrategicRoadMobility>
        <finalDistanceStratMob>200000</finalDistanceStratMob>
        <firstMaxSpeedForSlope>25</firstMaxSpeedForSlope>
        <firstSlopeCondition>0</firstSlopeCondition>
        <fourthMaxSpeedForSlope>8.33333333333333</fourthMaxSpeedForSlope>
        <fourthSlopeCondition>-0.1</fourthSlopeCondition>
        <maxPosOnBrakePedal>400</maxPosOnBrakePedal>
        <maxPosOnGasPedal>1</maxPosOnGasPedal>
        <samplingDistanceStratMob>10</samplingDistanceStratMob>
        <secondMaxSpeedForSlope>19.4444444444444</secondMaxSpeedForSlope>
        <secondSlopeCondition>-0.025</secondSlopeCondition>
        <thirdMaxSpeedForSlope>13.8888888888889</thirdMaxSpeedForSlope>
        <thirdSlopeCondition>-0.06</thirdSlopeCondition>
      </StrategicRoadMobility>
      <OperativeMobility>
        <finalDistanceOpMob>200</finalDistanceOpMob>
        <finalTimeOpMob>300</finalTimeOpMob>
        <firstMaxSpeedCondOpMob>25</firstMaxSpeedCondOpMob>
        <firstSlopeCondOpMob>0</firstSlopeCondOpMob>
        <fourthMaxSpeedCondOpMob>8.33333333333333</fourthMaxSpeedCondOpMob>
        <fourthSlopeCondOpMob>-0.1</fourthSlopeCondOpMob>
        <isGeneralCriteriaOpMob>1</isGeneralCriteriaOpMob>
        <isWarningOnlyCriteriaOpMob>1</isWarningOnlyCriteriaOpMob>
        <maxAccelOpMob>1</maxAccelOpMob>
        <maxDecelOpMob>4</maxDecelOpMob>
        <maxLateralOpMob>3</maxLateralOpMob>
        <secondMaxSpeedCondOpMob>19.4444444444444</secondMaxSpeedCondOpMob>
        <secondSlopeCondOpMob>-0.025</secondSlopeCondOpMob>
        <thirdMaxSpeedCondOpMob>13.8888888888889</thirdMaxSpeedCondOpMob>
        <thirdSlopeCondOpMob>-0.06</thirdSlopeCondOpMob>
      </OperativeMobility>
      <PrecomputationLap>
        <areInterimResultsFilesSaved>1</areInterimResultsFilesSaved>
        <isNewTrajSavedPrecomputationLap>1</isNewTrajSavedPrecomputationLap>
        <isResultFromStartLinePrecomputationLap>1</isResultFromStartLinePrecomputationLap>
        <minimalSpeed>8.33333333333333</minimalSpeed>
        <nbTurnPoints>20</nbTurnPoints>
      </PrecomputationLap>
      <DynamicLap>
        <brakingPointsPrecision>0.5</brakingPointsPrecision>
        <isBrakingPointsIteration>0</isBrakingPointsIteration>
        <isCircuitOpenedDynamicLap>1</isCircuitOpenedDynamicLap>
        <isRecordUpdatedTrajDynamicLap>1</isRecordUpdatedTrajDynamicLap>
        <isResultFromStartLineDynamicLap>1</isResultFromStartLineDynamicLap>
        <maxSideslipAngle>0.785398163397448</maxSideslipAngle>
        <maxTrajectoryError>2</maxTrajectoryError>
        <minSpeed>2.77777777777778</minSpeed>
        <timePrecision>0.01</timePrecision>
      </DynamicLap>
    </PredefinedRun>
    <ProgressDlg>
      <fullScreen>0</fullScreen>
      <playSound>0</playSound>
      <refreshRate>10</refreshRate>
      <showGraphs>0</showGraphs>
      <showView>0</showView>
      <ResultsGraph>
        <abcissa>131072</abcissa>
        <abcissaUnit>s</abcissaUnit>
        <tabName>Graph</tabName>
        <title>Graph</title>
      </ResultsGraph>
    </ProgressDlg>
    <ProjectInfos>
      <designOfExperimentName>Design of Experiment 1</designOfExperimentName>
      <explorationPath>/EVAL_ADAS_CTRL</explorationPath>
      <originalName>EVAL_ADAS_CTRL</originalName>
      <testPlanName>AEB</testPlanName>
      <testPlanPath>C:/AVSimulation/LOCAL_STUDIO_PATH/SCANeR-Samples-Pack-2023/bin/x64/analytics/AEB/AEB.xtp</testPlanPath>
    </ProjectInfos>
    <Recording>
      <mode>AUTO</mode>
      <recordPath></recordPath>
      <ModelHandlerRecorder>
        <enable>0</enable>
        <enableTrafficRecording>0</enableTrafficRecording>
        <isOneEvery>0</isOneEvery>
        <oneEvery>1</oneEvery>
        <samplePeriod>0.1</samplePeriod>
        <zipResultFile>0</zipResultFile>
      </ModelHandlerRecorder>
      <ScanerNetRecorder/>
    </Recording>
    <ScenarioStopCriteria>
      <finalTime>15</finalTime>
      <stopAtFinalTime>1</stopAtFinalTime>
    </ScenarioStopCriteria>
    <StoryBoard>
      <firstStep>Main Step</firstStep>
      <Step>
        <description></description>
        <hint></hint>
        <name>Main Step</name>
        <ScenarioScript>
          <isScriptActive>1</isScriptActive>
          <script>
TYPEOF SCENARIO (0)
{
	IS_EXPANDED="1"
	LABEL="Main"
	FILE="EVAL_ADAS_CTRL_Main"
	TASK_KIND="0"

	TYPEOF VARIABLE (0)
	{
		LABEL="distanceToCollision"
		TYPE="FLOAT"
		VALUE="11.000000"
		INTERACTIVE_TYPE="VOID"
		IS_INITIALIZATION_NEEDED_AT_START="1"
		INTERACTIVE_MIN_VALUE="1"
		INTERACTIVE_MAX_VALUE="200"
		INTERACTIVE_STEP_VALUE="1"
		CATEGORY="INTERNAL"
	}

	TYPEOF VARIABLE (5)
	{
		LABEL="rainLevel"
		TYPE="FLOAT"
		VALUE="1.000000"
		INTERACTIVE_TYPE="VOID"
		IS_INITIALIZATION_NEEDED_AT_START="0"
		INTERACTIVE_MIN_VALUE="0"
		INTERACTIVE_MAX_VALUE="9999"
		INTERACTIVE_STEP_VALUE="1"
		CATEGORY="INTERNAL"
	}

	TYPEOF VARIABLE (1)
	{
		LABEL="startToBrake"
		TYPE="FLOAT"
		VALUE="0.000000"
		INTERACTIVE_TYPE="VOID"
		IS_INITIALIZATION_NEEDED_AT_START="0"
		INTERACTIVE_MIN_VALUE="0"
		INTERACTIVE_MAX_VALUE="9999"
		INTERACTIVE_STEP_VALUE="1"
		CATEGORY="INTERNAL"
	}

	TYPEOF VARIABLE (2)
	{
		LABEL="brakingDistance"
		TYPE="FLOAT"
		VALUE="0.000000"
		INTERACTIVE_TYPE="VOID"
		IS_INITIALIZATION_NEEDED_AT_START="0"
		INTERACTIVE_MIN_VALUE="0"
		INTERACTIVE_MAX_VALUE="9999"
		INTERACTIVE_STEP_VALUE="1"
		CATEGORY="OUTPUT"
	}

	TYPEOF VARIABLE (4)
	{
		LABEL="isCollision"
		TYPE="FLOAT"
		VALUE="0.000000"
		INTERACTIVE_TYPE="VOID"
		IS_INITIALIZATION_NEEDED_AT_START="0"
		INTERACTIVE_MIN_VALUE="0"
		INTERACTIVE_MAX_VALUE="9999"
		INTERACTIVE_STEP_VALUE="1"
		CATEGORY="OUTPUT"
	}

	TYPEOF RULE (0)
	{
		LABEL="Rule: distanceToCollision is used as input by the ADAS"

		TYPEOF CONDITION (IS_TRUE)
		{
			IS_EXPANDED="1"
		}

		TYPEOF ACTION (EXPORT_CHANNEL)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (CHANNEL_ID)
			{
				KIND="EXPORT_CHANNEL"
				VALUE="67"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="VARIABLE"
				VALUE="0"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (1)
	{
		LABEL="Rule: Pedestrian cross road"

		TYPEOF CONDITION (IS_TRIGGERED_BY_VEHICLE)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (TRIGGER_NAME)
			{
				KIND="TRIGGER"
				VALUE="pedestrianActivation"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VHL_ACTIVATION)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="1"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (STATE)
			{
				KIND="ENUM"
				VALUE="STATE_ON"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (PEDESTRIAN_CROSS_ROAD)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="1"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (PEDESTRIAN_CARE_TRAFFIC)
			{
				KIND="ENUM"
				VALUE="FALSE"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (PEDESTRIAN_CROSSING_ANGLE)
			{
				KIND="USER"
				VALUE="90"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (6)
	{
		LABEL="Rule: normal conditions"

		TYPEOF CONDITION (EQUAL)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="VARIABLE"
				VALUE="5"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (7)
	{
		LABEL="Rule: rain conditions"

		TYPEOF CONDITION (INFERIOR)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="VARIABLE"
				VALUE="5"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="0.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="0.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="10.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="0.5"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (5)
	{
		LABEL="Rule: extra dry conditions"

		TYPEOF CONDITION (SUPERIOR)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="VARIABLE"
				VALUE="5"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_FRONT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_LEFT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1.5"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_ADHERENCE_NEW)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_AXLE)
			{
				KIND="ENUM"
				VALUE="VHL_AXLE_REAR"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_WHEEL_SIDE)
			{
				KIND="ENUM"
				VALUE="WHEEL_RIGHT"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1.5"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (4)
	{
		LABEL="Rule: Criteria isCollision with Ego"

		TYPEOF CONDITION (IS_VHL_COLLIDED)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VARIABLE)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VARIABLE_NAME)
			{
				KIND="VARIABLE"
				VALUE="4"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VARIABLE)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VARIABLE_NAME)
			{
				KIND="VARIABLE"
				VALUE="2"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="9999"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (GOTO_TASK)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (TASK_NUMBER)
			{
				KIND="ENUM"
				VALUE="GOTO_END_SCENARIO"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (8)
	{
		LABEL="Rule: unknown issue"

		TYPEOF CONDITION (IS_TRIGGERED_BY_VEHICLE)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (TRIGGER_NAME)
			{
				KIND="TRIGGER"
				VALUE="issue"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VARIABLE)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VARIABLE_NAME)
			{
				KIND="VARIABLE"
				VALUE="4"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="1"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VARIABLE)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VARIABLE_NAME)
			{
				KIND="VARIABLE"
				VALUE="2"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="USER"
				VALUE="9999"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (GOTO_TASK)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (TASK_NUMBER)
			{
				KIND="ENUM"
				VALUE="GOTO_END_SCENARIO"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF TASK (0)
	{
		IS_EXPANDED="1"
		LABEL="Task"
		TASK_KIND="0"

		TYPEOF RULE (2)
		{
			IS_EXPANDED="1"
			LABEL="Rule: Init braking distance"

			TYPEOF CONDITION (SUPERIOR)
			{
				MODIFIER="BECOMES_TRUE"

				TYPEOF PARAMETER (OPERAND_1)
				{
					KIND="FUNCTION"

					TYPEOF FUNCTION (GET_VHL_BRAKE)
					{

						TYPEOF PARAMETER (VHL_NUMBER)
						{
							KIND="USER"
							VALUE="0"
							OWNER_FILE=""
						}
					}
					OWNER_FILE=""
				}

				TYPEOF PARAMETER (OPERAND_2)
				{
					KIND="USER"
					VALUE="200"
					OWNER_FILE=""
				}
			}

			TYPEOF ACTION (SET_VARIABLE)
			{

				TYPEOF PARAMETER (VARIABLE_NAME)
				{
					KIND="VARIABLE"
					VALUE="1"
					OWNER_FILE=""
				}

				TYPEOF PARAMETER (FLOAT_VALUE)
				{
					KIND="FUNCTION"

					TYPEOF FUNCTION (GET_TRIPMETER)
					{

						TYPEOF PARAMETER (VHL_NUMBER)
						{
							KIND="USER"
							VALUE="0"
							OWNER_FILE=""
						}
					}
					OWNER_FILE=""
				}
			}

			TYPEOF ACTION (GOTO_TASK)
			{
				IS_EXPANDED="1"

				TYPEOF PARAMETER (TASK_NUMBER)
				{
					KIND="ENUM"
					VALUE="GOTO_NEXT_TASK"
					OWNER_FILE=""
				}
			}
		}
	}

	TYPEOF TASK (1)
	{
		IS_EXPANDED="1"
		LABEL="Task: Compute the braking distance"
		TASK_KIND="0"

		TYPEOF RULE (3)
		{
			IS_EXPANDED="1"
			LABEL="Rule"

			TYPEOF CONDITION (INFEQUAL)
			{

				TYPEOF PARAMETER (OPERAND_1)
				{
					KIND="FUNCTION"

					TYPEOF FUNCTION (GET_VHL_SPEED)
					{

						TYPEOF PARAMETER (VHL_NUMBER)
						{
							KIND="USER"
							VALUE="0"
							OWNER_FILE=""
						}
					}
					OWNER_FILE=""
				}

				TYPEOF PARAMETER (OPERAND_2)
				{
					KIND="USER"
					VALUE="1"
					OWNER_FILE=""
				}
			}

			TYPEOF ACTION (SET_VARIABLE)
			{

				TYPEOF PARAMETER (VARIABLE_NAME)
				{
					KIND="VARIABLE"
					VALUE="2"
					OWNER_FILE=""
				}

				TYPEOF PARAMETER (FLOAT_VALUE)
				{
					KIND="FUNCTION"

					TYPEOF FUNCTION (MINUS)
					{

						TYPEOF PARAMETER (OPERAND_1)
						{
							KIND="FUNCTION"

							TYPEOF FUNCTION (GET_TRIPMETER)
							{

								TYPEOF PARAMETER (VHL_NUMBER)
								{
									KIND="USER"
									VALUE="0"
									OWNER_FILE=""
								}
							}
							OWNER_FILE=""
						}

						TYPEOF PARAMETER (OPERAND_2)
						{
							KIND="VARIABLE"
							VALUE="1"
							OWNER_FILE=""
						}
					}
					OWNER_FILE=""
				}
			}

			TYPEOF ACTION (SET_VARIABLE)
			{

				TYPEOF PARAMETER (VARIABLE_NAME)
				{
					KIND="VARIABLE"
					VALUE="0"
					OWNER_FILE=""
				}

				TYPEOF PARAMETER (FLOAT_VALUE)
				{
					KIND="FUNCTION"

					TYPEOF FUNCTION (GET_VHL_CART_DISTANCE_TO_VEHICLE)
					{
						IS_EXPANDED="1"

						TYPEOF PARAMETER (VHL_NUMBER)
						{
							KIND="USER"
							VALUE="0"
							OWNER_FILE=""
						}

						TYPEOF PARAMETER (VHL_NUMBER)
						{
							KIND="USER"
							VALUE="1"
							OWNER_FILE=""
						}
					}
					OWNER_FILE=""
				}
			}
		}
	}
}
</script>
          <scriptLanguage>mice</scriptLanguage>
          <scriptName>Main</scriptName>
        </ScenarioScript>
      </Step>
      <Transition>
        <allConditionsTrue>1</allConditionsTrue>
        <fromStep>Main Step</fromStep>
        <name>Forward</name>
        <toStep>BUILTIN_SUCCESS_ADB568D064DB408EAFDE1D4021E336DF</toStep>
      </Transition>
      <Transition>
        <allConditionsTrue>0</allConditionsTrue>
        <fromStep>Main Step</fromStep>
        <name>Failure</name>
        <toStep>BUILTIN_FAILURE_A36CBB59761A4AF1B2BACC50D71084AB</toStep>
      </Transition>
      <Link>
        <linkedFrom>mice:/Main%20Step/Main/BrakingDistance</linkedFrom>
        <linkedTo>result:/BrakingDistance</linkedTo>
      </Link>
      <Link>
        <linkedFrom>mice:/Main%20Step/Main/DistanceFromPedestrian</linkedFrom>
        <linkedTo>result:/DistanceFromPedestrian</linkedTo>
      </Link>
      <Link>
        <linkedFrom>mice:/Main%20Step/Main/isCollision</linkedFrom>
        <linkedTo>result:/isCollision</linkedTo>
      </Link>
      <Link>
        <linkedFrom>mice:/Main%20Step/Main/brakingDistance</linkedFrom>
        <linkedTo>result:/brakingDistance</linkedTo>
      </Link>
      <Step>
        <description></description>
        <hint></hint>
        <name>_background_task_step</name>
      </Step>
      <Transition>
        <allConditionsTrue>0</allConditionsTrue>
        <fromStep>_background_task_step</fromStep>
        <name>_end_scenario_condition_list</name>
        <toStep>BUILTIN_SUCCESS_ADB568D064DB408EAFDE1D4021E336DF</toStep>
        <Condition>
          <description></description>
          <evaluationCount>-1</evaluationCount>
          <evaluationTimeout>0</evaluationTimeout>
          <evaluationType>IS_TRUE</evaluationType>
          <name>TimeOut</name>
          <TimeOutTest>
            <duration>15</duration>
          </TimeOutTest>
        </Condition>
      </Transition>
      <Transition>
        <allConditionsTrue>0</allConditionsTrue>
        <fromStep>_background_task_step</fromStep>
        <name>_failed_scenario_condition_list</name>
        <toStep>BUILTIN_FAILURE_A36CBB59761A4AF1B2BACC50D71084AB</toStep>
      </Transition>
    </StoryBoard>
    <UserDataList/>
    <Visual>
      <Others>
        <loadCache>0</loadCache>
        <optimize>1</optimize>
        <refreshRate>60</refreshRate>
        <viewMode></viewMode>
      </Others>
      <Quality>
        <anisotropicFiltering>8</anisotropicFiltering>
        <antiAliasing>8</antiAliasing>
        <fadeLOD>0</fadeLOD>
      </Quality>
      <RoadMarks>
        <mode></mode>
        <nodeName></nodeName>
        <Interval>
          <max>0</max>
          <min>0</min>
        </Interval>
      </RoadMarks>
      <Sfx>
        <dazzleHalo>1</dazzleHalo>
        <fog>1</fog>
        <fogHalo>1</fogHalo>
        <sky>1</sky>
      </Sfx>
      <Viewing>
        <farPlane>5000</farPlane>
        <nearPlane>1</nearPlane>
        <terrainLODScale>1</terrainLODScale>
        <vehicleLODScale>1</vehicleLODScale>
      </Viewing>
    </Visual>
    <Vehicle>
      <cabin></cabin>
      <decorationName></decorationName>
      <driveInReverse>0</driveInReverse>
      <driverId>0</driverId>
      <id>0</id>
      <initEngineRunning>1</initEngineRunning>
      <initialDistOnTrajectory>0</initialDistOnTrajectory>
      <initialSpeed>13.8888888888889</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>SmallFamilyCar</modelName>
      <motionId>-1</motionId>
      <name>EGO</name>
      <process>MODELHANDLER</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>0</state>
      <trailerId>-1</trailerId>
      <Equipments>
        <sensorConfigurationName>SmallFamilyCar</sensorConfigurationName>
        <SensorOutputProcs>
          <sensorUniqueId>300000</sensorUniqueId>
          <OutputProc>
            <outputName>sensorPointAnchor</outputName>
            <processName>Automatic</processName>
          </OutputProc>
        </SensorOutputProcs>
      </Equipments>
      <ItineraryRoadXml>
        <endBehaviour>0</endBehaviour>
      </ItineraryRoadXml>
      <Model>
        <Callas>
          <activeConfiguration>-1</activeConfiguration>
          <antiWheeling>0</antiWheeling>
          <applyGroundBodyInteractionForces>0</applyGroundBodyInteractionForces>
          <autoClutch>1</autoClutch>
          <brakeTemperature>313.15</brakeTemperature>
          <computeGroundBodyInteraction>0</computeGroundBodyInteraction>
          <computeGroundCanonInteraction>0</computeGroundCanonInteraction>
          <corneringStartType>0</corneringStartType>
          <cutThrottleOnGearChange>1</cutThrottleOnGearChange>
          <damperTemperature>313.15</damperTemperature>
          <delayShiftDownAfterDown>0.5</delayShiftDownAfterDown>
          <delayShiftDownAfterUp>0.5</delayShiftDownAfterUp>
          <delayShiftUpAfterDown>0.5</delayShiftUpAfterDown>
          <delayShiftUpAfterUp>0.5</delayShiftUpAfterUp>
          <detailedRuts>0</detailedRuts>
          <gearboxTemperature>373.15</gearboxTemperature>
          <initBatteryCharge>1</initBatteryCharge>
          <initialLateralAcceleration>0</initialLateralAcceleration>
          <initialSteeringAngle>0</initialSteeringAngle>
          <initialStepIncrement>0.0005</initialStepIncrement>
          <initialTurnRadius>0</initialTurnRadius>
          <isDelayShiftDownAfterDown>1</isDelayShiftDownAfterDown>
          <isDelayShiftDownAfterUp>1</isDelayShiftDownAfterUp>
          <isDelayShiftUpAfterDown>1</isDelayShiftUpAfterDown>
          <isDelayShiftUpAfterUp>1</isDelayShiftUpAfterUp>
          <isLockGearDuringCornering>0</isLockGearDuringCornering>
          <isParallelComputation>0</isParallelComputation>
          <limitManualGearChoice>0</limitManualGearChoice>
          <lockGearDuringCorneringAngle>3.14159265358979</lockGearDuringCorneringAngle>
          <modulesTimeout>30</modulesTimeout>
          <numericalMethod>1</numericalMethod>
          <oilTemperature>353.15</oilTemperature>
          <regulateBrakePedal>0</regulateBrakePedal>
          <staticStateComputation>0</staticStateComputation>
          <tireTemperature>313.15</tireTemperature>
          <toeHealOnDownshift>0</toeHealOnDownshift>
          <waterTemperature>353.15</waterTemperature>
          <CustomData/>
          <Hack>
            <useNewMovementEquations>1</useNewMovementEquations>
            <useNewWheelDOF>1</useNewWheelDOF>
          </Hack>
        </Callas>
      </Model>
      <ObjectPosition>
        <heading>0</heading>
        <position>11.7790470123291 0 0</position>
        <RoadPosition>
          <abscissa>11.7790470123291</abscissa>
          <gapInItnSystem>0</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Track</track>
          <zOffset>0</zOffset>
        </RoadPosition>
      </ObjectPosition>
      <StopCriteria>
        <finalDistance>100000</finalDistance>
        <finalTime>20</finalTime>
        <maxSideslipAngle>0.261799387799149</maxSideslipAngle>
        <maxSideslipAngleSpeed>0.349065850398866</maxSideslipAngleSpeed>
        <maxSpeed>111.111111111111</maxSpeed>
        <maxTrajectoryError>3</maxTrajectoryError>
        <minSpeed>0.277777777777778</minSpeed>
        <stopCanonContact>0</stopCanonContact>
        <stopConeCollision>0</stopConeCollision>
        <stopFinalDistance>0</stopFinalDistance>
        <stopFinalTime>1</stopFinalTime>
        <stopLateralAccelerationPeek>0</stopLateralAccelerationPeek>
        <stopMaxSpeed>0</stopMaxSpeed>
        <stopMinSpeed>0</stopMinSpeed>
        <stopSideslipAngle>0</stopSideslipAngle>
        <stopSideslipAngleSpeed>0</stopSideslipAngleSpeed>
        <stopSpin>0</stopSpin>
        <stopStableMovement>0</stopStableMovement>
        <stopStall>0</stopStall>
        <stopStallDuration>1</stopStallDuration>
        <stopStandstill>0</stopStandstill>
        <stopTrajectoryError>0</stopTrajectoryError>
        <stopWheelLift>0</stopWheelLift>
      </StopCriteria>
      <Swarm>
        <appearBackRadius>250</appearBackRadius>
        <appearFrontRadius>500</appearFrontRadius>
        <density>1</density>
        <disappearBackRadius>500</disappearBackRadius>
        <disappearFrontRadius>1000</disappearFrontRadius>
        <frontAppearFactor>0.75</frontAppearFactor>
        <queen>-1</queen>
        <queenDirectionFactor>0.3</queenDirectionFactor>
      </Swarm>
    </Vehicle>
    <Driver>
      <driverName>Driver 0</driverName>
      <driverType>VirtualDriver</driverType>
      <id>0</id>
      <process>ACQUISITION</process>
      <HumanDriver>
        
      </HumanDriver>
      <AirplaneDriver>
        <Trajectory>
          <isClosed>0</isClosed>
          <isWithObstacles>0</isWithObstacles>
          <notes></notes>
          <type>0</type>
          <CurvatureTrajectory>
            <initialHeading>0</initialHeading>
            <initialPosition>0 0</initialPosition>
          </CurvatureTrajectory>
          <XYTrajectory>
            <interpolationType>0</interpolationType>
          </XYTrajectory>
        </Trajectory>
      </AirplaneDriver>
      <VirtualDriver>
        <Command>
          <externalCommandReading>0</externalCommandReading>
          <ignoreThrottleOnBraking>0</ignoreThrottleOnBraking>
          <isDifferentialsLocking>0</isDifferentialsLocking>
          <isExhaustBrake>0</isExhaustBrake>
          <isPlow>0</isPlow>
          <isRetarder>0</isRetarder>
          <isSkidSteering>0</isSkidSteering>
          <isTransfer>0</isTransfer>
          <isTurret>0</isTurret>
          <isWind>0</isWind>
          <notes></notes>
          <pilotCommandReading>0</pilotCommandReading>
          <steeringInputType>0</steeringInputType>
          <type>0</type>
          <AnalyticCommand>
            <acceleratorAmplitude>1</acceleratorAmplitude>
            <acceleratorAscendingTime>1</acceleratorAscendingTime>
            <acceleratorBasicSignal>0</acceleratorBasicSignal>
            <acceleratorDescendingTime>1</acceleratorDescendingTime>
            <acceleratorDuration>10</acceleratorDuration>
            <acceleratorInitialTime>0</acceleratorInitialTime>
            <brakeAmplitude>400</brakeAmplitude>
            <brakeAscendingTime>1</brakeAscendingTime>
            <brakeBasicSignal>0</brakeBasicSignal>
            <brakeDescendingTime>1</brakeDescendingTime>
            <brakeDuration>10</brakeDuration>
            <brakeInitialTime>0</brakeInitialTime>
            <gear>1</gear>
            <skidAmplitude>0.4</skidAmplitude>
            <skidAmplitude1>0.4</skidAmplitude1>
            <skidAmplitude2>0</skidAmplitude2>
            <skidAngularSpeed>0.4</skidAngularSpeed>
            <skidBasicSignal>0</skidBasicSignal>
            <skidDuration1>5</skidDuration1>
            <skidDuration2>1</skidDuration2>
            <skidDuration3>1</skidDuration3>
            <skidInitialTime>0</skidInitialTime>
            <skidNumber>1</skidNumber>
            <skidPeriode>5</skidPeriode>
            <skidSeparatedBy>0</skidSeparatedBy>
            <skidSignal>0</skidSignal>
            <steeringAmplitude>1.5707963267949</steeringAmplitude>
            <steeringAmplitude1>1.5707963267949</steeringAmplitude1>
            <steeringAmplitude2>0</steeringAmplitude2>
            <steeringAngularSpeed>1.5707963267949</steeringAngularSpeed>
            <steeringBasicSignal>0</steeringBasicSignal>
            <steeringDuration1>2</steeringDuration1>
            <steeringDuration2>1</steeringDuration2>
            <steeringDuration3>1</steeringDuration3>
            <steeringInitialTime>0</steeringInitialTime>
            <steeringNumber>1</steeringNumber>
            <steeringPeriode>5</steeringPeriode>
            <steeringSeparatedBy>0</steeringSeparatedBy>
            <steeringSignal>0</steeringSignal>
            <windAmplitude>20</windAmplitude>
            <windAscendingTime>0.1</windAscendingTime>
            <windAzimuth>1.5707963267949</windAzimuth>
            <windBasicSignal>0</windBasicSignal>
            <windDescendingTime>0.1</windDescendingTime>
            <windDuplique>0</windDuplique>
            <windDuration>5</windDuration>
            <windInitialTime>0</windInitialTime>
            <windInterval>1</windInterval>
            <windPeriode>5</windPeriode>
            <windPulseTime>1</windPulseTime>
            <windSigne>0</windSigne>
          </AnalyticCommand>
          <ExternalCorrections>
            <additiveBrakeRetarderNotch>0</additiveBrakeRetarderNotch>
            <additiveGunAimAngle>0</additiveGunAimAngle>
            <additiveNbShot>0</additiveNbShot>
            <additiveShotRythm>0</additiveShotRythm>
            <additiveTargetPosition>0 0 0</additiveTargetPosition>
            <additiveTurretAimAngle>0</additiveTurretAimAngle>
            <additiveWindAzimuth>0</additiveWindAzimuth>
            <additiveWindSpeed>0</additiveWindSpeed>
            <multiplicativeBrakeRetarderNotch>1</multiplicativeBrakeRetarderNotch>
            <multiplicativeGunAimAngle>1</multiplicativeGunAimAngle>
            <multiplicativeNbShot>1</multiplicativeNbShot>
            <multiplicativeShotRythm>1</multiplicativeShotRythm>
            <multiplicativeTargetPosition>1 1 1</multiplicativeTargetPosition>
            <multiplicativeTurretAimAngle>1</multiplicativeTurretAimAngle>
            <multiplicativeWindAzimuth>1</multiplicativeWindAzimuth>
            <multiplicativeWindSpeed>1</multiplicativeWindSpeed>
          </ExternalCorrections>
          <PilotCorrections>
            <additiveAcceleratorPos>0</additiveAcceleratorPos>
            <additiveBrakingForce>0</additiveBrakingForce>
            <additiveClutchPos>0</additiveClutchPos>
            <additiveHandBrakeForce>0</additiveHandBrakeForce>
            <additiveSpeedTarget>0</additiveSpeedTarget>
            <additiveSteeringAngle>0</additiveSteeringAngle>
            <additiveSteeringSkid>0</additiveSteeringSkid>
            <additiveSteeringTorque>0</additiveSteeringTorque>
            <additiveYawSpeedTarget>0</additiveYawSpeedTarget>
            <multiplicativeAcceleratorPos>1</multiplicativeAcceleratorPos>
            <multiplicativeBrakingForce>1</multiplicativeBrakingForce>
            <multiplicativeClutchPos>1</multiplicativeClutchPos>
            <multiplicativeHandBrakeForce>1</multiplicativeHandBrakeForce>
            <multiplicativeSpeedTarget>1</multiplicativeSpeedTarget>
            <multiplicativeSteeringAngle>1</multiplicativeSteeringAngle>
            <multiplicativeSteeringSkid>1</multiplicativeSteeringSkid>
            <multiplicativeSteeringTorque>1</multiplicativeSteeringTorque>
            <multiplicativeYawSpeedTarget>1</multiplicativeYawSpeedTarget>
          </PilotCorrections>
          <PilotCommandPoint>
            <acceleratorPos>0</acceleratorPos>
            <brakingForce>0</brakingForce>
            <clutchPos>0</clutchPos>
            <distance>0</distance>
            <gear>1</gear>
            <handBrakeForce>0</handBrakeForce>
            <speedTarget>13.8888888888889</speedTarget>
            <steeringAngle>0</steeringAngle>
            <steeringSkid>0</steeringSkid>
            <steeringTorque>0</steeringTorque>
            <time>0</time>
            <yawSpeedTarget>0</yawSpeedTarget>
          </PilotCommandPoint>
          <PilotCommandPoint>
            <acceleratorPos>0</acceleratorPos>
            <brakingForce>0</brakingForce>
            <clutchPos>0</clutchPos>
            <distance>0</distance>
            <gear>1</gear>
            <handBrakeForce>0</handBrakeForce>
            <speedTarget>13.8888888888889</speedTarget>
            <steeringAngle>0</steeringAngle>
            <steeringSkid>0</steeringSkid>
            <steeringTorque>0</steeringTorque>
            <time>30</time>
            <yawSpeedTarget>0</yawSpeedTarget>
          </PilotCommandPoint>
        </Command>
        <LateralPilot>
          <circlePilotVal>50</circlePilotVal>
          <fixedSteeringWheelAngle>0</fixedSteeringWheelAngle>
          <startOnTrajectory>0</startOnTrajectory>
          <type>1</type>
          <Trajectory>
            <isClosed>0</isClosed>
            <isWithObstacles>0</isWithObstacles>
            <notes></notes>
            <type>0</type>
            <CurvatureTrajectory>
              <initialHeading>0</initialHeading>
              <initialPosition>0 0</initialPosition>
            </CurvatureTrajectory>
            <XYTrajectory>
              <interpolationType>0</interpolationType>
            </XYTrajectory>
          </Trajectory>
          <TrajectoryPilot>
            <armsCrossing>0</armsCrossing>
            <deltaCurvature>0.5</deltaCurvature>
            <deltaCurvatureDT>0.5</deltaCurvatureDT>
            <deltaDirection>0.5</deltaDirection>
            <deltaDirectionDT>0.5</deltaDirectionDT>
            <deltaPosition>0.5</deltaPosition>
            <deltaPositionDT>0.5</deltaPositionDT>
            <limitSteeringWithOptimalSideslipAngle>0</limitSteeringWithOptimalSideslipAngle>
            <maxSteeringAcceleration>34.9065850398866</maxSteeringAcceleration>
            <maxSteeringSpeed>17.4532925199433</maxSteeringSpeed>
            <maxSteeringTorque>50</maxSteeringTorque>
            <posTrajectorySensor>0</posTrajectorySensor>
            <predictionGain>0</predictionGain>
            <previsionTime>0.5</previsionTime>
            <pulse>6</pulse>
            <tireUsage>0.5</tireUsage>
            <trajCurv1>0.1</trajCurv1>
            <trajCurv2>0.005</trajCurv2>
            <trajSpeed1>8.33333333333333</trajSpeed1>
            <trajSpeed2>55.5555555555556</trajSpeed2>
            <trajTargetDist1>8</trajTargetDist1>
            <trajTargetDist2>20</trajTargetDist2>
            <trajTargetDistMod1>1</trajTargetDistMod1>
            <trajTargetDistMod2>1.2</trajTargetDistMod2>
            <trajectoryReading>1</trajectoryReading>
            <type>0</type>
          </TrajectoryPilot>
        </LateralPilot>
        <LengthwisePilot>
          <accCurvature1>0.1</accCurvature1>
          <accCurvature2>0.005</accCurvature2>
          <accGasPedal1>0.01</accGasPedal1>
          <accGasPedal2>0.05</accGasPedal2>
          <accGasPedalDepressTime1>0.5</accGasPedalDepressTime1>
          <accGasPedalDepressTime2>0.05</accGasPedalDepressTime2>
          <accGasPedalPressTime1>2</accGasPedalPressTime1>
          <accGasPedalPressTime2>0.1</accGasPedalPressTime2>
          <accIsControlDrift>0</accIsControlDrift>
          <accMaxTireUseRate>0.9</accMaxTireUseRate>
          <accSpeed1>13.8888888888889</accSpeed1>
          <accSpeed2>55.5555555555556</accSpeed2>
          <accTrajOffset>0.1</accTrajOffset>
          <autoSpeedProfile>0</autoSpeedProfile>
          <brakingBrakePedalPressTime1>0.5</brakingBrakePedalPressTime1>
          <brakingBrakePedalPressTime2>0.1</brakingBrakePedalPressTime2>
          <brakingCurvature1>0.1</brakingCurvature1>
          <brakingCurvature2>0.005</brakingCurvature2>
          <delayBetweenAccAndBrake>0</delayBetweenAccAndBrake>
          <enableABS>1</enableABS>
          <enableESP>1</enableESP>
          <enableTractionControl>1</enableTractionControl>
          <forceLockup>0</forceLockup>
          <gapTimeBetweenvehicles>2</gapTimeBetweenvehicles>
          <gearboxMode>10</gearboxMode>
          <isRatioLimit>0</isRatioLimit>
          <lockupDiffMode>0</lockupDiffMode>
          <maxAcceleration>3</maxAcceleration>
          <maxDeceleration>3</maxDeceleration>
          <maxLateralAcceleration>3</maxLateralAcceleration>
          <maxRatio>5</maxRatio>
          <maxSpeed>25</maxSpeed>
          <minRatio>1</minRatio>
          <profileSpeedFactor>1</profileSpeedFactor>
          <transferChoice>1</transferChoice>
          <type>1</type>
          <vehicleTarget>-1</vehicleTarget>
        </LengthwisePilot>
      </VirtualDriver>
    </Driver>
    <Vehicle>
      <cabin></cabin>
      <decorationName></decorationName>
      <driveInReverse>0</driveInReverse>
      <driverId>1</driverId>
      <id>1</id>
      <initEngineRunning>1</initEngineRunning>
      <initialDistOnTrajectory>0</initialDistOnTrajectory>
      <initialSpeed>0</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>Man_European_03</modelName>
      <motionId>-1</motionId>
      <name>Pedestrian</name>
      <process>WALKERTRAFFIC</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>1</state>
      <trailerId>-1</trailerId>
      <Equipments>
        <sensorConfigurationName></sensorConfigurationName>
      </Equipments>
      <ItineraryRoadXml>
        <endBehaviour>0</endBehaviour>
      </ItineraryRoadXml>
      <Model/>
      <ObjectPosition>
        <heading>0</heading>
        <position>136.289337158203 -4.655 0.1</position>
        <RoadPosition>
          <abscissa>136.289337158203</abscissa>
          <gapInItnSystem>4.655</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Track</track>
          <zOffset>0</zOffset>
        </RoadPosition>
      </ObjectPosition>
      <StopCriteria>
        <finalDistance>100000</finalDistance>
        <finalTime>3600</finalTime>
        <maxSideslipAngle>0.261799387799149</maxSideslipAngle>
        <maxSideslipAngleSpeed>0.349065850398866</maxSideslipAngleSpeed>
        <maxSpeed>111.111111111111</maxSpeed>
        <maxTrajectoryError>3</maxTrajectoryError>
        <minSpeed>0.277777777777778</minSpeed>
        <stopCanonContact>0</stopCanonContact>
        <stopConeCollision>0</stopConeCollision>
        <stopFinalDistance>0</stopFinalDistance>
        <stopFinalTime>0</stopFinalTime>
        <stopLateralAccelerationPeek>0</stopLateralAccelerationPeek>
        <stopMaxSpeed>0</stopMaxSpeed>
        <stopMinSpeed>0</stopMinSpeed>
        <stopSideslipAngle>0</stopSideslipAngle>
        <stopSideslipAngleSpeed>0</stopSideslipAngleSpeed>
        <stopSpin>0</stopSpin>
        <stopStableMovement>0</stopStableMovement>
        <stopStall>0</stopStall>
        <stopStallDuration>1</stopStallDuration>
        <stopStandstill>0</stopStandstill>
        <stopTrajectoryError>0</stopTrajectoryError>
        <stopWheelLift>0</stopWheelLift>
      </StopCriteria>
      <Swarm>
        <appearBackRadius>250</appearBackRadius>
        <appearFrontRadius>500</appearFrontRadius>
        <density>1</density>
        <disappearBackRadius>500</disappearBackRadius>
        <disappearFrontRadius>1000</disappearFrontRadius>
        <frontAppearFactor>0.75</frontAppearFactor>
        <queen>-1</queen>
        <queenDirectionFactor>0.3</queenDirectionFactor>
      </Swarm>
    </Vehicle>
    <Driver>
      <driverName>Driver 1</driverName>
      <driverType>TrafficDriver</driverType>
      <id>1</id>
      <process>WALKERTRAFFIC</process>
      <TrafficDriver>
        <accelCurveObserving>1</accelCurveObserving>
        <accelEmergencyPedestrianObserving>1</accelEmergencyPedestrianObserving>
        <accelEmergencyVehicleObserving>1</accelEmergencyVehicleObserving>
        <accelFollowObserving>1</accelFollowObserving>
        <accelRegulationObserving>1</accelRegulationObserving>
        <autonomousToDriverTransitionTime>1</autonomousToDriverTransitionTime>
        <brakePedalThreashold>1</brakePedalThreashold>
        <disconectSteeringWhenAutonomous>1</disconectSteeringWhenAutonomous>
        <driverToAutonomousTransitionTime>5</driverToAutonomousTransitionTime>
        <gasPedalThreashold>0.01</gasPedalThreashold>
        <ignoreDriverPeriod>4</ignoreDriverPeriod>
        <laneGapMean>0</laneGapMean>
        <laneGapPeriodMean>0</laneGapPeriodMean>
        <laneGapPeriodStdDev>0</laneGapPeriodStdDev>
        <laneGapStdDev>0.2</laneGapStdDev>
        <manualOverrideModule></manualOverrideModule>
        <maxSpeed>0.988888888888889</maxSpeed>
        <norm>NormalDriver_Pedestrian</norm>
        <overtakeRisk>-0.11</overtakeRisk>
        <priorityObserving>1</priorityObserving>
        <safetyTime>0.78</safetyTime>
        <signObserving>1</signObserving>
        <speedLimitRisk>0.98</speedLimitRisk>
        <stayOnLane>0</stayOnLane>
        <steeringTorqueThreashold>5</steeringTorqueThreashold>
        <strategyFile>default</strategyFile>
      </TrafficDriver>
      <AirplaneDriver>
        <Trajectory>
          <isClosed>0</isClosed>
          <isWithObstacles>0</isWithObstacles>
          <notes></notes>
          <type>0</type>
          <CurvatureTrajectory>
            <initialHeading>0</initialHeading>
            <initialPosition>0 0</initialPosition>
          </CurvatureTrajectory>
          <XYTrajectory>
            <interpolationType>0</interpolationType>
          </XYTrajectory>
        </Trajectory>
      </AirplaneDriver>
    </Driver>
    <Trigger>
      <filter>*</filter>
      <height>4</height>
      <isActivated>1</isActivated>
      <isRectangle>1</isRectangle>
      <name>pedestrianActivation</name>
      <width>6.5</width>
      <ObjectPosition>
        <heading>0</heading>
        <position>86.0802917480469 0 0</position>
        <RoadPosition>
          <abscissa>86.0802917480469</abscissa>
          <gapInItnSystem>-0</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Track</track>
          <zOffset>0</zOffset>
        </RoadPosition>
      </ObjectPosition>
    </Trigger>
    <ScenarioCriterion>
      <green>brakingDistance &lt; 20</green>
      <name>Braking distance</name>
      <red>brakingDistance &gt;= 25</red>
      <yellow>brakingDistance &gt;= 20 and brakingDistance &lt; 25</yellow>
    </ScenarioCriterion>
    <ScenarioCriterion>
      <green>isCollision == 0</green>
      <name>Collision</name>
      <red>isCollision == 1</red>
      <yellow>isCollision == -1</yellow>
    </ScenarioCriterion>
    <ScenarioOutput>
      <name>brakingDistance</name>
      <unit>Unit not found</unit>
    </ScenarioOutput>
    <ScenarioOutput>
      <name>isCollision</name>
      <unit>Unit not found</unit>
    </ScenarioOutput>
    <Trigger>
      <filter>*</filter>
      <height>4</height>
      <isActivated>1</isActivated>
      <isRectangle>1</isRectangle>
      <name>issue</name>
      <width>6.5</width>
      <ObjectPosition>
        <heading>0</heading>
        <position>182.906616210938 0 0</position>
        <RoadPosition>
          <abscissa>182.906616210938</abscissa>
          <gapInItnSystem>0</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Track</track>
          <zOffset>0</zOffset>
        </RoadPosition>
      </ObjectPosition>
    </Trigger>
    <VariadicParameter>
      <description></description>
      <id>/sce/Scenario/StoryBoard/Step[name/@ScenarioTreeValue="Main Step"]/ScenarioScript[scriptName="Main"]/Variable[name=5]/value</id>
      <name>rainLevel</name>
      <unit></unit>
      <RealParameter>
        <defaultValue>1.000000</defaultValue>
        <RealRange>
          <max>1.000000</max>
          <min>1.000000</min>
        </RealRange>
      </RealParameter>
    </VariadicParameter>
    <VariadicParameter>
      <description></description>
      <id>/sce/Scenario/StoryBoard/Step[name/@ScenarioTreeValue="Main Step"]/ScenarioScript[scriptName="Main"]/Variable[name=0]/value</id>
      <name>distanceToCollision</name>
      <unit></unit>
      <RealParameter>
        <defaultValue>11.000000</defaultValue>
        <RealRange>
          <max>11.000000</max>
          <min>11.000000</min>
        </RealRange>
      </RealParameter>
    </VariadicParameter>
  </Scenario>

</sce>
