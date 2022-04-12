
#pragma once

#pragma warning (disable : 4231)

#include "stk/STK.h"

#include <iostream>
#include <vector>

namespace stk {

class Vector2;

class STK_API Vector3
{
public:
	Vector3();
	Vector3(const double xx, const double yy, const double zz);
	Vector3(const Vector3& other);
	//! return the norm of the vector
	double getNorm() const;
	//! return the square of the norm of the vector
	//! takes less CPU time than getNorm() as it does not extract the square root
	//! useful when testing if the norm is null or if comparing to another square speed
	double getNormSquared() const;
	//! distance from one point to another, same as (A-B).getNorm()
	double getDistance(const Vector3& rhs) const;
	//! changes the length of  vector, does nothing if the vector is null
	bool setNorm(double newMagnitude);
	//! set the norm of a vector to 1
	bool normalize(double zeroTolerance = 0);
	//! same as == operator but with an optional delta tolerance for equality
	bool isEqual(const Vector3& compareVec, double zeroTolerance = 0) const;
	//! rotate the vector around an axis aligned with K by angle K.getNorm()
	void rotate(const Vector3& K);
	//! assignemnt operator overload
	Vector3& operator=(const Vector3& v);
	//! divide a vector by a scalar value
	Vector3& operator/=(const double scalar);
	//! multiply  vector by a scalar value
	Vector3& operator*=(const double scalar);
	//! add a vector to the current vector
	Vector3& operator+=(const Vector3& v);
	//! subtract a vector to the current vector
	Vector3& operator-=(const Vector3& v);
	//! dot product of two vectors (returns a scalar value)
	double operator*(const Vector3& b) const;
	//! vectorial product
	Vector3 operator^(const Vector3& b) const;
	//! divide a vector by a scalar value
	Vector3 operator/(const double	s) const;
	//! multiply a vector by a scalar value
	Vector3 operator*(const double s) const;
	//! add two vectors
	Vector3 operator+(const Vector3& b) const;
	//! subtract two vectors
	Vector3 operator-(const Vector3& b) const;
	//! return the opposite of the vector
	Vector3 operator-() const;
	//! check the equality of two vectors, should only be used with stk::Vecotr(0,0,0)...
	bool operator==(const Vector3& rhs) const;
	//! check the inequality of two vectors, should only be used with stk::Vecotr(0,0,0)...
	bool operator!=(const Vector3& rhs) const;

//legacy, do not use
	Vector3 operator/(const Vector3& b) const;
	Vector3& operator/=(const Vector3& v);
	Vector3 operator%(const Vector3& b) const;
	operator const Vector2&() const {return *reinterpret_cast<const Vector2*>(this);}
	operator Vector2&() {return *reinterpret_cast<Vector2*>(this);}
public:
	double x;
	double y;
	double z;
};

STK_API Vector3 operator*(double s, const Vector3& v);
STK_API Vector3 Center(const Vector3& v0, const Vector3& v1);
	// in the interval [-pi,+pi] radians
STK_API double angleBetweenVectors( const Vector3& v1, const Vector3& v2 );
STK_API double angleBetweenNormalizedVectors( const Vector3& v1, const Vector3& v2 );

STK_API std::ostream& operator<<(std::ostream& out, const Vector3& p);
STK_API std::istream& operator>>(std::istream& in, Vector3& p);

}

#ifdef WIN32
STK_EXT template class STK_API std::allocator<stk::Vector3>;
STK_EXT template class STK_API std::vector<stk::Vector3>;
#endif

