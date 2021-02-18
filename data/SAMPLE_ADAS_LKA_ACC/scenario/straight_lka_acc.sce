<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<sce version="20.21.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

  <Scenario>
    <description>To use this scenario:
- Start the following modules: ACQUISITION, MODELHANDLER, SENSORS, VISUAL
+
LATERALCTRL
Note: LATERALCTRL is a SCANeR API module provided in C/C++ (the source code is eval_lateral_ctrl.cpp).

This scenario demonstrates how to control the steering wheel of an EGO vehicle depending of the road markings.
The scenario to use with this configuration is “EVAL_LATERAL_CTRL”.
In this scenario, the human driver only controls the longitudinal part of the EGO vehicle.
The lateral part, steering wheel of the EGO vehicle, follows the road curvature. 
To detect the road curvature a camera sensor for road markings detection is used.
The sensors configuration is: markingDetection
The camera sensor model used is: FrontCamera_Lanes_Lines</description>
    <name></name>
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
      <name>long_highway.rnd</name>
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
      <finalTime>3600</finalTime>
      <stopAtFinalTime>0</stopAtFinalTime>
    </ScenarioStopCriteria>
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
    <ScenarioScript>
      <isScriptActive>1</isScriptActive>
      <script>
TYPEOF SCENARIO (0)
{
	IS_EXPANDED="1"
	LABEL="Main"
	FILE="straight_lka_acc_Main"
	TASK_KIND="0"

	TYPEOF VARIABLE (0)
	{
		LABEL="ACC_target_speed"
		TYPE="FLOAT"
		VALUE="70"
		INTERACTIVE_TYPE="INTEGER"
		IS_INITIALIZATION_NEEDED_AT_START="1"
		INTERACTIVE_MIN_VALUE="30"
		INTERACTIVE_MAX_VALUE="200"
		INTERACTIVE_STEP_VALUE="10"
		CATEGORY="INTERNAL"
	}

	TYPEOF RULE (0)
	{
		IS_EXPANDED="1"
		LABEL="Export Channel"

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
				VALUE="66"
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
		IS_EXPANDED="1"
		LABEL="ACC mode"

		TYPEOF CONDITION (SUPERIOR)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="FUNCTION"

				TYPEOF FUNCTION (GET_CUSTOM_INPUT)
				{
					IS_EXPANDED="1"

					TYPEOF PARAMETER (VHL_NUMBER)
					{
						KIND="VEHICLE"
						VALUE="0"
						OWNER_FILE=""
					}

					TYPEOF PARAMETER (VEHICLE_CUSTOM_INPUT)
					{
						KIND="VHC_INPUT"
						VALUE="1"
						OWNER_FILE=""
					}
				}
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_CUSTOM_INPUT)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="0"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (VEHICLE_CUSTOM_INPUT)
			{
				KIND="VHC_INPUT"
				VALUE="2"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (STATE)
			{
				KIND="ENUM"
				VALUE="STATE_ON"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (FLOAT_VALUE)
			{
				KIND="FUNCTION"

				TYPEOF FUNCTION (MODULO)
				{
					IS_EXPANDED="1"

					TYPEOF PARAMETER (OPERAND_1)
					{
						KIND="FUNCTION"

						TYPEOF FUNCTION (PLUS)
						{
							IS_EXPANDED="1"

							TYPEOF PARAMETER (OPERAND_1)
							{
								KIND="FUNCTION"

								TYPEOF FUNCTION (GET_CUSTOM_INPUT)
								{
									IS_EXPANDED="1"

									TYPEOF PARAMETER (VHL_NUMBER)
									{
										KIND="VEHICLE"
										VALUE="0"
										OWNER_FILE=""
									}

									TYPEOF PARAMETER (VEHICLE_CUSTOM_INPUT)
									{
										KIND="VHC_INPUT"
										VALUE="2"
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
						OWNER_FILE=""
					}

					TYPEOF PARAMETER (OPERAND_2)
					{
						KIND="USER"
						VALUE="5"
						OWNER_FILE=""
					}
				}
				OWNER_FILE=""
			}
		}
	}
}
</script>
      <scriptLanguage></scriptLanguage>
      <scriptName>Main</scriptName>
    </ScenarioScript>
    <Vehicle>
      <cabin></cabin>
      <decorationName></decorationName>
      <driveInReverse>0</driveInReverse>
      <driverId>0</driverId>
      <id>0</id>
      <initEngineRunning>1</initEngineRunning>
      <initialDistOnTrajectory>0</initialDistOnTrajectory>
      <initialSpeed>0</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>ExecutiveCar_lka_acc_2021</modelName>
      <motionId>-1</motionId>
      <name>ExecutiveCar_lka_acc</name>
      <process>MODELHANDLER</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>0</state>
      <trailerId>-1</trailerId>
      <Equipments>
        <sensorConfigurationName>FrontDetection</sensorConfigurationName>
        <SensorOutputProcs>
          <sensorUniqueId>300000</sensorUniqueId>
          <OutputProc>
            <outputName>sensorPointAnchor</outputName>
            <processName>Automatic</processName>
          </OutputProc>
        </SensorOutputProcs>
        <SensorOutputProcs>
          <sensorUniqueId>100000</sensorUniqueId>
          <OutputProc>
            <outputName>sensorPoint</outputName>
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
        <position>-5.65440601051405e-15 -1.74999999996894 0</position>
        <RoadPosition>
          <abscissa>9990</abscissa>
          <gapInItnSystem>-1.75</gapInItnSystem>
          <relativeHeading>3.14159265358979</relativeHeading>
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
      <driverName>Driver 0</driverName>
      <driverType>HumanDriver</driverType>
      <id>0</id>
      <process>ACQUISITION</process>
      <HumanDriver>
        <ConfigurationFile></ConfigurationFile>
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
        <maxSpeed>36.1111111111111</maxSpeed>
        <norm>NormalDriver</norm>
        <overtakeRisk>0</overtakeRisk>
        <priorityObserving>1</priorityObserving>
        <safetyTime>2.5</safetyTime>
        <signObserving>1</signObserving>
        <speedLimitRisk>1</speedLimitRisk>
        <stayOnLane>0</stayOnLane>
        <steeringTorqueThreashold>5</steeringTorqueThreashold>
        <strategyFile>default</strategyFile>
      </TrafficDriver>
    </Driver>
    <Vehicle>
      <cabin></cabin>
      <decorationName></decorationName>
      <driveInReverse>0</driveInReverse>
      <driverId>2</driverId>
      <id>1</id>
      <initEngineRunning>1</initEngineRunning>
      <initialDistOnTrajectory>0</initialDistOnTrajectory>
      <initialSpeed>13.8888888888889</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>Peugeot_108_Kilt</modelName>
      <motionId>-1</motionId>
      <name>Peugeot_108_Kilt</name>
      <process>TRAFFIC</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>0</state>
      <trailerId>-1</trailerId>
      <Equipments>
        <sensorConfigurationName></sensorConfigurationName>
      </Equipments>
      <ItineraryRoadXml>
        <endBehaviour>0</endBehaviour>
      </ItineraryRoadXml>
      <Model>
        <Simple/>
      </Model>
      <ObjectPosition>
        <heading>0</heading>
        <position>9.99999999999999 -1.74999999996911 0</position>
        <RoadPosition>
          <abscissa>9980</abscissa>
          <gapInItnSystem>-1.75000000000013</gapInItnSystem>
          <relativeHeading>3.14159274101257</relativeHeading>
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
      <driverName>Driver 2</driverName>
      <driverType>TrafficDriver</driverType>
      <id>2</id>
      <process>TRAFFIC</process>
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
        <maxSpeed>13.8888888888889</maxSpeed>
        <norm>NormalDriver</norm>
        <overtakeRisk>-0.09</overtakeRisk>
        <priorityObserving>1</priorityObserving>
        <safetyTime>1.62</safetyTime>
        <signObserving>1</signObserving>
        <speedLimitRisk>0.98</speedLimitRisk>
        <stayOnLane>1</stayOnLane>
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
  </Scenario>

</sce>
