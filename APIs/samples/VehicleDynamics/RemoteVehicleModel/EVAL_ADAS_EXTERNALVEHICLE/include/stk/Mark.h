
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"

#include <iostream>

namespace stk {

class STK_API Mark
{
public:
	Mark();
	Mark(const Vector3& pos, double roll, double pitch, double heading);
	Mark(const Vector3& pos, const Vector3& rot);
	//! get the center offset of the frame
	Vector3 getOrigin() const;
	bool operator== (const Mark& a) const;
	bool operator!= (const Mark& a) const;
	//! offset the origine of the frame
	Mark operator+ (const Vector3& a) const;
	Mark operator- (const Vector3& a) const;
	Mark& operator+= (const Vector3& a);
	Mark& operator-= (const Vector3& a);

//begin legacy (do not use...)
	operator const Vector3&() const {return *reinterpret_cast<const Vector3*>(this);}
	operator Vector3&() {return *reinterpret_cast<Vector3*>(this);}
//end legacy
public:
	//! x axis pointing forward
	double x;
	//! y axis pointing left
	double y;
	//! z axis pointing up
	double z;
	//! rotation around the X axis
	double roll;
	//! rotation around the Y axis
	double pitch;
	//! rotation around the Z axis
	double heading;
};

STK_API std::ostream &operator<<(std::ostream &out, const Mark &r);
STK_API std::istream &operator>>(std::istream &in, Mark &r);

}
