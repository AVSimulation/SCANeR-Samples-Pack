
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"

#include <vector>

namespace stk {

class STK_API Vector2
{		
public:
	Vector2();
	Vector2(double xx, double yy);

	//! return the norm of the vector
	double	getNorm() const; 
	//! return the square of the norm of the vector
	//! takes ess CPU time than getNorm() as it noes not extract the square root
	//! useful when testing if the norm is null or if comparing to another square speed
	double	getNormSquared() const;
	//! distance from one point to another, same as (A-B).getNorm()
	double	getDistance(const Vector2& rhs) const;
	//! changes the length of  vector, does nothing if the vector is null
	bool	setNorm(double newMagnitude);
	//! set the norm of a vector to 1
	bool	normalize(double zeroTolerance = 0);
	//! same as == operator but with an optional delta tolerance for equality
	bool	isEqual(const Vector2& compareVec, double	zeroTolerance = 0) const;
	//! divide a vector by a scalar value
	Vector2&	operator/=(double scalar);
	//! multiply  vector by a scalar value
	Vector2&	operator*=(double scalar);
	//! add a vector to the current vector
	Vector2&	operator+=(const Vector2& v);
	//! subtract a vector to the current vector
	Vector2&	operator-=(const Vector2& v);
	//! divide a vector by a scalar value
	Vector2 operator/(double s) const;
	//! multiply a vector by a scalar value
	Vector2 operator*(double s) const;
	//! add two vectors
	Vector2 operator+(const Vector2& b) const;
	//! subtract two vectors
	Vector2 operator-(const Vector2& b) const;
	//! return the opposite of the vector
	Vector2 operator-() const;
	//! check the equality of two vectors, should only be used with stk::Vecotr(0,0)...
	bool  operator==(const Vector2& rhs) const;
	//! check the inequality of two vectors, should only be used with stk::Vecotr(0,0)...
	bool  operator!=(const Vector2& right) const;
	//! dot product of two vectors (returns a scalar value)
	double operator*(const Vector2& b) const;
	//! vectorial product
	double operator^(const Vector2& b) const;

//legacy, do not use
	double	getArgument() const; // result is ]-pi; pi] (rounding gives ]-pi; pi[)
	Vector2 operator%(const Vector2& b) const;
public:
	double x;
	double y;
};

STK_API Vector2 operator*(double s, const Vector2& pos);
// in the interval [-pi,+pi] radians
STK_API double angleBetweenVectors( const Vector2& v1, const Vector2& v2 );
STK_API double angleBetweenNormalizedVectors( const Vector2& v1, const Vector2& v2 );

STK_API Vector2 toVector2(const Vector3& pos);

STK_API Vector2 center(const Vector2& v0, const Vector2& v1);

STK_API std::ostream& operator<<(std::ostream& out, const Vector2& p);
STK_API std::istream& operator>>(std::istream& in, Vector2& p);

}

#ifdef WIN32
STK_EXT template class STK_API std::allocator<stk::Vector2>;
STK_EXT template class STK_API std::vector<stk::Vector2>;
#endif
