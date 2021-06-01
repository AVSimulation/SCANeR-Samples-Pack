<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<sce version="20.21.1" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

  <Scenario>
    <description></description>
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
      <name>Meung2.rnd</name>
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
        <isCircuitOpenedDynamicLap>0</isCircuitOpenedDynamicLap>
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
      <finalTime>10</finalTime>
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
	FILE="cameraOutputs_Main"
	TASK_KIND="0"

	TYPEOF RULE (1)
	{
		IS_EXPANDED="1"
		LABEL="Rule: Move pedestrian out of beam after 5s"

		TYPEOF CONDITION (SUPEQUAL)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="FUNCTION"

				TYPEOF FUNCTION (GET_SCENARIO_CLOCK)
				{
				}
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="2"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VHL_POSITION)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="1"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_XPOSITION)
			{
				KIND="USER"
				VALUE="190.954"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_YPOSITION)
			{
				KIND="USER"
				VALUE="3708.98"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (HEADING)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (2)
	{
		IS_EXPANDED="1"
		LABEL="Rule: Move car out of beam after 10s"

		TYPEOF CONDITION (SUPEQUAL)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="FUNCTION"

				TYPEOF FUNCTION (GET_SCENARIO_CLOCK)
				{
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

		TYPEOF ACTION (SET_VHL_POSITION)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="2"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_XPOSITION)
			{
				KIND="USER"
				VALUE="186.295"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_YPOSITION)
			{
				KIND="USER"
				VALUE="3714.54"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (HEADING)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
			}
		}
	}

	TYPEOF RULE (0)
	{
		IS_EXPANDED="1"
		LABEL="Rule: Move car in beam after 15s"

		TYPEOF CONDITION (SUPEQUAL)
		{
			IS_EXPANDED="1"
			MODIFIER="BECOMES_TRUE"

			TYPEOF PARAMETER (OPERAND_1)
			{
				KIND="FUNCTION"

				TYPEOF FUNCTION (GET_SCENARIO_CLOCK)
				{
				}
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (OPERAND_2)
			{
				KIND="USER"
				VALUE="8"
				OWNER_FILE=""
			}
		}

		TYPEOF ACTION (SET_VHL_POSITION)
		{
			IS_EXPANDED="1"

			TYPEOF PARAMETER (VHL_NUMBER)
			{
				KIND="VEHICLE"
				VALUE="2"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_XPOSITION)
			{
				KIND="USER"
				VALUE="294.059"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (MAP_YPOSITION)
			{
				KIND="USER"
				VALUE="3785.22"
				OWNER_FILE=""
			}

			TYPEOF PARAMETER (HEADING)
			{
				KIND="USER"
				VALUE="0"
				OWNER_FILE=""
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
      <initialSpeed>0</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>BMW_S3_Black_Sapphire</modelName>
      <motionId>-1</motionId>
      <name>BMW_S3_Black_Sapphire</name>
      <process>TRAFFIC</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>1</state>
      <trailerId>-1</trailerId>
      <Equipments>
        <sensorConfigurationName>bmw</sensorConfigurationName>
        <SensorOutputProcs>
          <sensorUniqueId>100000</sensorUniqueId>
          <OutputProc>
            <outputName>sensorPointAnchor</outputName>
            <processName>Automatic</processName>
          </OutputProc>
          <OutputProc>
            <outputName>sensorTargetBBox</outputName>
            <processName>Automatic</processName>
          </OutputProc>
          <OutputProc>
            <outputName>cameraImage</outputName>
            <processName>CAMERASENSOR</processName>
          </OutputProc>
        </SensorOutputProcs>
      </Equipments>
      <ItineraryRoadXml>
        <endBehaviour>0</endBehaviour>
      </ItineraryRoadXml>
      <Model>
        <Simple/>
      </Model>
      <ObjectPosition>
        <heading>0.611333310604095</heading>
        <position>189.981314542428 3712.60560514136 10.0284339153176</position>
        <RoadPosition>
          <abscissa>3378.28681548072</abscissa>
          <gapInItnSystem>1.74999999999983</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Branche automatique 33</track>
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
      <driverType>TrafficDriver</driverType>
      <id>0</id>
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
        <maxSpeed>38.8888888888889</maxSpeed>
        <norm>NormalDriver</norm>
        <overtakeRisk>0.5</overtakeRisk>
        <priorityObserving>1</priorityObserving>
        <safetyTime>2.5</safetyTime>
        <signObserving>1</signObserving>
        <speedLimitRisk>1.1</speedLimitRisk>
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
      <modelName>Kid_Boy_Winter_01</modelName>
      <motionId>-1</motionId>
      <name>Kid_Boy_Winter_01</name>
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
        <heading>0.611333310604095</heading>
        <position>221.963173850039 3730.71111393568 10.1296038259267</position>
        <RoadPosition>
          <abscissa>3414.8680657802</abscissa>
          <gapInItnSystem>5.28000000000007</gapInItnSystem>
          <relativeHeading>0</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Branche automatique 33</track>
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
    <Vehicle>
      <cabin></cabin>
      <decorationName></decorationName>
      <driveInReverse>0</driveInReverse>
      <driverId>2</driverId>
      <id>2</id>
      <initEngineRunning>1</initEngineRunning>
      <initialDistOnTrajectory>0</initialDistOnTrajectory>
      <initialSpeed>0</initialSpeed>
      <modelColor>0 0 0</modelColor>
      <modelName>BMW_S3_Melbourne_Red</modelName>
      <motionId>-1</motionId>
      <name>BMW_S3_Melbourne_Red</name>
      <process>TRAFFIC</process>
      <recomputeRestitutionMovement>1</recomputeRestitutionMovement>
      <state>1</state>
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
        <heading>3.75292587280273</heading>
        <position>218.51483774349 3736.87901675867 10.0043375018232</position>
        <RoadPosition>
          <abscissa>3415.58440867129</abscissa>
          <gapInItnSystem>-1.74999999999982</gapInItnSystem>
          <relativeHeading>3.14159250259399</relativeHeading>
          <subNetwork>Sub Network</subNetwork>
          <track>Branche automatique 33</track>
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
        <maxSpeed>33.2527777777778</maxSpeed>
        <norm>NormalDriver</norm>
        <overtakeRisk>-0.13</overtakeRisk>
        <priorityObserving>1</priorityObserving>
        <safetyTime>1.54</safetyTime>
        <signObserving>1</signObserving>
        <speedLimitRisk>0.97</speedLimitRisk>
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
  </Scenario>

</sce>
