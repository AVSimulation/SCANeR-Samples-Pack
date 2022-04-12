
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"
#include "stk/Transform.h"

#include <iostream>

namespace stk {

class STK_API Torser
{
public:
	Torser(const Vector3& PtAppli = Vector3(0,0,0),
		const Vector3&  Force = Vector3(0,0,0),
		const Vector3&  Moment = Vector3(0,0,0));
	Torser(const Torser &T);

	Torser TorseurEquivalent(const Vector3& NouveauPoint) const; 

	// le T1 operator() T2 gere le déplacement du torseur T2 au meme point que T1
	// Valable pour + - += -= ==
	Torser operator+(const Torser& A) const;
	Torser operator-(const Torser& A) const;
	Torser& operator+=(const Torser& A);
	Torser& operator-=(const Torser& A);

	Torser& operator=(const Torser& A);

	bool operator==(const Torser& A) const;

	void dump(std::ostream& out, const char* nom);
	
public:
	//private:
 Vector3 applicationPoint;
 Vector3 force;
 Vector3 moment;
};

STK_API void ApplyTrans(const Transform& M, Torser& T);

}
