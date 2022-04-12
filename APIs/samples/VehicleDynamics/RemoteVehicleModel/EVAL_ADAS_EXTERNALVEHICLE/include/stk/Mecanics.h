
#pragma once
#include "stk/Vector3.h"

namespace stk {

STK_API stk::Vector3 AbsoluteAccelerationAtPoint(const stk::Vector3& AccelerationAbsolueG,	//vecteur acceleration de G dans le repere global
								const stk::Vector3& Wterre,		//vecteur vitesse rotation instantannée	dans le repere global
								const stk::Vector3& dWterre,		//vecteur acceleration rotation  instantannée dans le repere global
								const stk::Vector3& GM);			//Vecteur GM dans le repere global

}
