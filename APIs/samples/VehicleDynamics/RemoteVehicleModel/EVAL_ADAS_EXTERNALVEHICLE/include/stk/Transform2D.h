#pragma once

#include "stk/Matrix.h"
#include "stk/Vector2.h"
#include "math.h"

namespace stk
{
	//matrix of the form :
	//	[ rs00 rs01 tx ]
	//	[ rs10 rs11 ty ]
	//	[ 0    0    1  ]

	class STK_API Transform2D : public stk::Matrix
	{
	public:
		Transform2D();
		Transform2D(const stk::Vector2& translation, double rotation);

		// Set the matrix with the direct transform
		void localToGlobal(const stk::Vector2& translation, const stk::Vector2& scaling, double rotation);
		// Set the matrix with the inverse transform
		void globalToLocal(const stk::Vector2& translation, const stk::Vector2& scaling, double rotation);

		//Transform a 2D point using the transformation matrix 
		stk::Vector2 apply(const stk::Vector2 &v) const;

	private:
	};
}