/****************************************************************************************************

		Color.h
		Copyright: (c) AVSimulation. All rights reserved.

		Author:	Julien
		Date:	mercredi 25 janvier 2006

****************************************************************************************************/
#pragma once

#include "stk/STK.h"
#include "stk/Vector3.h"

#include <iostream>
#include <sstream>
#include <string>

namespace stk {

// This is the floating point color
class STK_API Color 
{
public:
	static const Color kBlack; 	// (0,0,0,1);
	static const Color kWhite;	// (1,1,1,1);
	static const Color kGrey;	// (0.5,0.5,0.5,1);
	static const Color kRed; 	// (1,0,0,1);
	static const Color kGreen; 	// (0,1,0,1);
	static const Color kBlue; 	// (0,0,1,1);
	static const Color kYellow; // (1,1,0,1);
	
public:
	// constructors/setters
	Color();
	Color(const double rr, const double gg, const double bb, const double aa=1.0);
	Color(const std::string& color);

	std::string name() const;
	
	bool isEqual(const Color& rhs, const double epsilon = 0.0) const;		
	
	// see if the color falls in between [0, 1]	- mainly for debug		
	bool		IsClamped() const;
	
	// clamp the color value to between [0, 1]
	void		Clamp();
	
	// these are operators on all the components
	bool		 operator==	(const Color& rhs) const;
	bool		 operator!=	(const Color& rhs) const;
	
	Color& operator=  (const double i);
	Color& operator+= (const Color& rhs);
	Color& operator-= (const Color& rhs);
	Color& operator*= (const double s);
	Color& operator/= (const double s);

	Color  operator+	(const Color& rhs) const;
	Color  operator-	(const Color& rhs) const;
	Color  operator*	(const double s) const;
	Color  operator/	(const double s) const;
	
	// returns the address of first component in the structure
	const double* GetAddrFirstComponent() const;
	
public:
	double red;
	double green;
	double blue;
	double alpha;
};

STK_API std::ostream& operator<< (std::ostream& out, const Color& color);
STK_API std::istream& operator>> (std::istream& in, Color& color);

/*
* \brief Convert the HSL vector into Color (RGB)
* \param[in] hsl the hsl vector
*/
STK_API Color ConvertHSLtoRGB(Vector3& hsl);


/*
* \brief Convert the Color into HSL vector (Hue - Saturation - Lightness)
* \returns the corresponding hsl vector
*/
STK_API Vector3 ConvertRGBtoHSL(Color& rgb);

}
