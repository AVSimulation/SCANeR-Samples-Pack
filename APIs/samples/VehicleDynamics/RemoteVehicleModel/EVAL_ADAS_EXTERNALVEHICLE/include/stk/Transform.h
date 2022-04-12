
#pragma once

#include "stk/STK.h"
#include "stk/Mark.h"
#include "stk/Matrix.h"

#include <vector>

namespace stk {

	STK_API stk::Matrix createScaleMatrix(const stk::Vector3& scale);

	STK_API stk::Matrix createPosMatrix(const stk::Mark& pos);

	class STK_API Transform : public Matrix
	{
	public:
		//! Construct an identity tranformation
		Transform();

		//! Destructor
		virtual ~Transform();

		//! Copy constructor
		Transform(const Matrix& mat);
		Transform& operator= (const Matrix& mat);

		//! T.localToGlobal(F) will initialize the transform T so that, if p is the coordinates of a point in the F frame, then "T.apply(p)"
		//! is the coordinates of the point in the T frame
		//! this transformation is the inverse of T.globalToLocal(F)
		void localToGlobal(double roll, double pitch, double heading, const Vector3& D);
		void localToGlobal(const Mark& Rep);

		//! T.globalToLocal(F) will initialize the transform T so that, if p is the coordinates of a point in the global frame, then "T.apply(p)"
		//! is the coordinates of the point in the F frame
		//! this transformation is the inverse of T.localToGlobal(F)
		void globalToLocal(double roll, double pitch, double heading, const Vector3& D);
		void globalToLocal(const Mark& Rep);

		//! apply the trasformation to P and return it.
		//! The transformation must be initialized by localToGlobal() ou globalToLocal() first
		Vector3 apply(const Vector3& P) const;
		//! apply only the translation component of the transformation, not the rotation
		Vector3 applyTranslation(const Vector3& P) const;
		//! apply only the rotation component of the transformation, not the translation
		Vector3 applyRotation(const Vector3& P) const;

		//! 
		virtual bool inverse();

		Mark toMark() const;

		bool operator==(const stk::Transform& other);
	};
}

#pragma warning(push)
#pragma warning(disable : 4231)
	STK_EXPORT_COMPARE(stk::Transform)
	STK_EXPORT_VECTOR(stk::Transform)
#pragma warning(pop)


