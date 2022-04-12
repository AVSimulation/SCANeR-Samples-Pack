
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"
#include "stk/Transform.h"

namespace stk {

class STK_API InertialMatrix
{
public:	
	InertialMatrix();
	InertialMatrix(const InertialMatrix& other);
	//InertialMatrix(const Solide& S);
	InertialMatrix(double Ixx, double Iyy,double Izz, const Vector3& PosCoG, double Masse);
	InertialMatrix(double Ixx, double Iyy,double Izz,
						double Ixy, double Ixz, double Iyz,
						const Vector3& PosCoG, double Masse);

	InertialMatrix operator+(const InertialMatrix& Mat) const;
	InertialMatrix& operator=(const InertialMatrix& Mat);

	void changePoint(const Vector3& NewPoint);
	void applyTransformation(const Transform& MT);

	//fonctions juste pour aider, a ne pas sur utiliser
	double getMass() const;
	const Vector3& getPosCoG() const;
	double getInertia(int i, int j) const;	
	//Solide getSolide() const;

	//j ai l accel angulaire, quel est le couple
	friend STK_API Vector3 computeTorque(const InertialMatrix& MI, const Vector3& AngularAccel);
	//j ai le couple, quel est l accel angulaire
	friend STK_API Vector3 computeAngularAccel(const InertialMatrix& MI, const Vector3& Torque);

private:
	Vector3 posCoG;
	double massSolid;
	Matrix data;
};

//j ai l accel angulaire, quel est le couple
STK_API Vector3 computeTorque(const InertialMatrix& MI, const Vector3& AngularAccel);
//j ai le couple, quel est l accel angulaire
STK_API Vector3 computeAngularAccel(const InertialMatrix& MI, const Vector3& Torque);

}
