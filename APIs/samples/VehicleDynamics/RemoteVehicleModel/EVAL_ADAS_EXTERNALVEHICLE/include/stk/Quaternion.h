
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"

namespace stk {

class STK_API Quaternion
{
public:
	Quaternion();
	Quaternion(double s, const Vector3& v);

	bool operator== (const Quaternion &Q) const;
	bool operator!= (const Quaternion &Q) const;

	Quaternion operator* (const Quaternion&Q) const;
	
	Quaternion operator* (double e) const;
	Quaternion operator/ (double e) const;
	Quaternion &operator*= (double e);
	Quaternion &operator/= (double e);

	Quaternion operator+ (const Quaternion&Q) const;
	Quaternion operator- (const Quaternion& Q) const;
	Quaternion &operator+= (const Quaternion&Q);
	Quaternion &operator-= (const Quaternion&Q);

	double getNorm() const;

//divise le vecteur par sa norme...	
	void normalize();

public:
	double s;
	Vector3 v;
};

STK_API void VectorRotationToQuaternion(stk::Vector3 v, double rot, Quaternion& q);
STK_API void EulerAnglesToQuaternion(double Roulis, double Tangage, double Lacet, Quaternion& q);
STK_API void QuaternionToEulerAngles(const Quaternion& q, double& Roulis, double& Tangage, double& Lacet);
STK_API void NormaliseCoordQuaternion(double& S, double& Vx, double& Vy, double& Vz);
STK_API Vector3 ApplyRotation(const Quaternion& q, const Vector3& Vin);

}
