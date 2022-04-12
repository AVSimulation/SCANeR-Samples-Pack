#ifndef _ModelWheelContact_
#define _ModelWheelContact_
#include "DriverOutput.h"
//	Wheel generic obj.
//	This object is a wrap class. It can be derived to implement one's own class and
//	road surface interrogation system
//	One available implementation is WheelRQ
//

#include "stk/Mark.h"
#include "stk/Unit.h"
#include "ITN/LaneType.h"
#include "ITN/GroundType.h"

namespace cats
{
	namespace model
	{
		//! Wheel data computed by the model
		/*! Some of this data is computed during the road query, another part by the model itself.
		*/
		struct WheelContact
		{
			WheelContact() : 
				myIsInContact(true), myPosition(0.0, 0.0, 0.0), myNormal(0.0, 0.0, 1.0),
				myRoadGrip(0), myLSR(0), mySlipAngle(0), 
				myGroundIndex(-1),
				myObjectId(-1),
				myLaneType(ITN::eLanePaved),
				myGroundType(ITN::eGroundAsphalt),
				myRoughnessHeight(0.005),
				myRoughnessLength(0.01),
				myRoughnessHeightStdDeviation(0),
				myRoughnessLengthStdDeviation(0),
				myLSROpt(0),
				mySlipAngleOpt(0),
				myWaterHeight(0)

			 {}

			//! the wheel is in contact with the road
			bool						myIsInContact;

			//!position of the point of contact
			stk::Vector3				myPosition;
			//! normal of the point of contact
			stk::Vector3				myNormal;	

			//! from 0 to 1
			double						myRoadGrip;

			//! 
			int							myGroundIndex;
			//! index of the object under the wheel
			int							myObjectId;

			//! vhl's wheels pseudo skid (Sx)
			double						myLSR;
			double						myLSROpt;
			//! vhl's wheels deviation (delta)
			double						mySlipAngle;
			double						mySlipAngleOpt;

			stk::Vector3				myTireForce;

			ITN::LaneType				myLaneType;
			double						myRoughnessHeight;
			double						myRoughnessLength;
			double						myRoughnessHeightStdDeviation;
			double						myRoughnessLengthStdDeviation;
			double						myWaterHeight;
			ITN::GroundType				myGroundType;
		};

		//! Wheel data computed by the model
		/*! Some of this data is computed during the road query, another part by the model itself.
		*/
		struct WheelState
		{
			WheelState() : myRotation(0), myRotationSpeed(0), myBrakeTemperature(0), myAbsIsActive(false) {}

			//!position of the center of the wheel holder (the hub).
			/*! in the Vehicle frame (center of the rear axle z=0 on ground, x forward, z up)
			*/
			stk::Mark			myHubPosition;

			//! wheel's (absolute) rotation around Pitch axis on the hub, in rad
			double			myRotation;
			
			//! wheel's (absolute) rotation speed Pitch axis on the hub, in rad/s
			double			myRotationSpeed;
			
			//! in Celsius
			double			myBrakeTemperature;

			/*! Description:	state abs braking system in the dynamic model<br>
			Unit, range:	0: abs off 1: abs on*/
			bool			myAbsIsActive;

			WheelContact	myWheelContact;

		};
	} // namespace model
} // namespace cats

#endif
