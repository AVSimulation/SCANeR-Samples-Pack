#pragma once

#include "stk/STK.h"
#include "stk/Vector2.h"
#include "stk/Vector3.h"
#include "stk/Quaternion.h"
#include "stk/Mark.h"
#include "stk/Transform.h"

#define EPSILON 0.000001

namespace stk {
	STK_API long lround(double x);

	STK_API Vector3 barycenter(double M1, const Vector3& Pt1, double M2, const Vector3& Pt2);
	STK_API Vector2 barycenter(double M1, const Vector2& Pt1, double M2, const Vector2& Pt2);
	STK_API double  barycenter(double m1, double x1, double m2, double x2);


	STK_API double square(double value);

	//retourne "B est compris entre [A C[ ou [C A["
	STK_API bool contains(double A, double B, double C);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Query if 'B' is in [A, C] or [C, A]. 
	/// \param	A	first bound. 
	/// \param	B	Tested value. 
	/// \param	C	second bound. 
	/// \return	true if it succeeds, false if it fails. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool contains2(double A, double B, double C);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Query if [a1, a2] and [b1, b2] Overlaps. 
	///
	///			If true compute the overlap interval.
	/// \param	a1			The first inteval bound.
	/// \param	a2			The first inteval bound. 
	/// \param	b1			The second inteval bound. 
	/// \param	b2			The second inteval bound. 
	/// \param [in,out]	r1	result bound. 
	/// \param [in,out]	r2	result bound. 
	/// \return	true if it overlaps, false if not. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool overlaps(double a1, double a2, double b1, double b2, double& r1, double& r2);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Query if [a1, a2] and [b1, b2] Overlaps. 
	///
	/// \param	a1			The first inteval bound.
	/// \param	a2			The first inteval bound. 
	/// \param	b1			The second inteval bound. 
	/// \param	b2			The second inteval bound. 
	/// \return	true if it overlaps, false if not. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool overlaps(double a1, double a2, double b1, double b2);

	//exemple2: LimitModulo(-PI, x, PI) retourne l'angle entre -PI et PI
	//exemple2: LimitModulo(0, x, 2*PI) retourne l'angle entre 0 et 2*PI
	STK_API double limitModulo(double min, double x, double max);
	STK_API double modulo(double Angle, double Max); //idem LimitModulo(0, Angle, Max)

	STK_API double safeACos(double x);

	//interpolation lineaire
	inline double intlin(double y1, double y2, double x1, double x2, double x) {
		const double DeltaX = x2 - x1;
		if (DeltaX != 0.0) return y1 + (x - x1) * (y2 - y1) / DeltaX;
		else return (y2 + y1) * 0.5;
	}
	STK_API double intlinAngle(double y1, double y2, double x1, double x2, double x);
	STK_API Mark intlin(const Mark &P1, const Mark &P2, double x1, double x2, double x);
	inline Vector2 intlin(const Vector2& P1, const Vector2& P2, double x1, double x2, double x) { return Vector2(intlin(P1.x, P2.x, x1, x2, x), intlin(P1.y, P2.y, x1, x2, x)); }
	inline Vector3 intlin(const Vector3& P1, const Vector3& P2, double x1, double x2, double x) { return Vector3(intlin(P1.x, P2.x, x1, x2, x), intlin(P1.y, P2.y, x1, x2, x), intlin(P1.z, P2.z, x1, x2, x)); }

	STK_API Vector3 apply(const Mark& ref, const Vector3& p);
	STK_API Mark convertFromAtUp(const Vector3& From, const Vector3& At, const Vector3& Up);
	STK_API Mark toMark(const Vector3& O, const Vector3& X, const Vector3& Y, const Vector3& Z);
	STK_API void decompose(const Mark& Rep, Vector3& X, Vector3& Y, Vector3& Z, Vector3& O);

	STK_API Vector3 normalePlan(const Vector3 &Pt1, const Vector3 &Pt2, const Vector3 &Pt3, double* D);
	STK_API bool intersectionSegmentPlan(const Vector3& Pt1, const Vector3& Pt2, const Vector3& Normale, double D, Vector3 *Sortie);
	STK_API bool intersectionDroitePlan(const Vector3& Pt1, const Vector3& Pt2, const Vector3& Normale, double D, Vector3 *Sortie);
	STK_API bool intersectLinePlane(const Vector3& P0, // first point on the line
		const Vector3& P1, // second point on the line
		const Vector3& V0, // point on the plane
		const Vector3& normal, // normal to the plane
		Vector3& result, //intersection result in global coordinates
		bool LimitToSegment = false
		);
	STK_API double distancePointPlan(const Vector3& P, const Vector3& V0, const Vector3& Normal);
	STK_API double distancePointPlanSigne(const Vector3& P, const Vector3& V0, const Vector3& Normal);
	STK_API double distancePointLine(const Vector3& P, const Vector3& V0, const Vector3& Normal);

	///-------------------------------------------------------------------------------------------------
	/// \brief	compute angle of a point on an a circle related to an other point. 
	///
	/// \param	center	The circle center. 
	/// \param	radius	The circle radius. 
	/// \param	begin	The base point, must be on the circle. 
	/// \param	point	The point to compute the angle, must be on the circle. 
	/// \return	The angle. 
	///-------------------------------------------------------------------------------------------------
	STK_API double angleOnCircle(const stk::Vector2& center, double radius, const stk::Vector2&  begin, const stk::Vector2& point);


	//"Intersect" est l'intersection du segment [A1 A2] et du segment [B1 B2] 
	STK_API bool intersectSegment(const Vector2& A1, const Vector2& A2, const Vector2& B1, const Vector2& B2, Vector2& Intersect);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Compute segments intersection. 
	/// \param	A1					The first extremity of the fist segment. 
	/// \param	A2					The second extremity of the fist segment. 
	/// \param	B1					The first extremity of the second segment. 
	/// \param	B2					The second extremity of the second segment. 
	/// \param 	Intersect	the founded intersection if any. 
	/// \param 	parameterA	the intersection parameter on the first segment (from A1 to A2 : 0..1). 
	/// \param 	parameterB	the intersection parameter on the second segment (from B1 to B2 : 0..1). 
	/// \return	true if it succeeds, false if it fails. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool intersectSegment(const Vector2& A1, const Vector2& A2, const Vector2& B1, const Vector2& B2, Vector2& Intersect, double& parameterA, double& parameterB);


	//!	compute intersection of 2 line define by 2 points
	/*!
		\param A1 first point of the first line
		\param A2 second point of the first line
		\param B1 first point of the second line
		\param B2 second point of the second line
		\param Intersect intersction point
		\return true if the 2 line instersect eachother, in that case Intersect is filled with the intersection point
		*/
	STK_API bool intersectLine(const Vector2& A1, const Vector2& A2, const Vector2& B1, const Vector2& B2, Vector2& Intersect);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Intersect circle line. 
	///
	/// \param	center			The circle center. 
	/// \param	radius			The circle radius. 
	/// \param	begin			The first point of the line. 
	/// \param	end				The second point of the line. 
	/// \param	points			The interstion points computed. 
	/// \param	parameters		Parameters [0..1] on the segment [begin end] of the results. 
	/// \param	limitToSegment	true to limit to segment @see intersectSegementLine. 
	/// \return	The number of intersections found. 
	///-------------------------------------------------------------------------------------------------
	STK_API int intersectCircleLine(const stk::Vector2& center, double radius, const stk::Vector2& begin, const stk::Vector2& end, stk::Vector2 points[2], double parameters[2], bool limitToSegment = false);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Intersect circle and a segment. 
	///
	/// \param	center		The circle center. 
	/// \param	radius		The circle radius. 
	/// \param	begin		The begin point of the segment. 
	/// \param	end			The end point of the segment. 
	/// \param	points		The interstion points computed. 
	/// \param	parameters	Parameters [0..1] on the segment [begin end] of the results. 
	/// \return	The number of intersections found. 
	///-------------------------------------------------------------------------------------------------
	STK_API int intersectCircleSegment(const stk::Vector2& center, double radius, const stk::Vector2& begin, const stk::Vector2& end, stk::Vector2 points[2], double parameters[2]);

	///-------------------------------------------------------------------------------------------------
	/// \brief	compute circles intersections. 
	///
	/// \param	center1	The first center. 
	/// \param	radius1	The first radius. 
	/// \param	center2	The second center. 
	/// \param	radius2	The second radius. 
	/// \param	point	The pointresult array. 
	/// \return number of founded intersections. 
	///-------------------------------------------------------------------------------------------------
	STK_API int intersectCircle(const stk::Vector2& center1, double radius1,
		const stk::Vector2& center2, double radius2,
		stk::Vector2 point[2]);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Rotates a 2D vector using the trigonometric convention. 
	/// \param [in,out]	v	the vector. 
	/// \param	angle		The angle in radians (trigonometric way, positive to the left). 
	/// \return	true if it succeeds, false if it fails. 
	///-------------------------------------------------------------------------------------------------
	STK_API void rotate(Vector2& v, double angle);

	STK_API void quaternionToMatriceTransfo(const Quaternion& q, const stk::Vector3& d, stk::Transform& mt);
	STK_API void matriceTransfoToQuaternion(const stk::Transform& m, Quaternion& q);

	STK_API bool isEqual(const double value1, const double value2, const double epsilon = 0);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Truncate a double with a certain number of decimals to keep.
	/// \param	d	the double to truncate.
	/// \param	numberOfDecimalsToKeep	the number of decimals to keep.
	/// \return	the truncated double.
	///-------------------------------------------------------------------------------------------------
	STK_API double TruncateToDecimal(const double& d, unsigned int numberOfDecimalsToKeep);
	///-------------------------------------------------------------------------------------------------
	/// \brief	Query if 'point' is on right of a lane define by 2 points. 
	/// \param	point	The point. 
	/// \param	A		A point of the lane. 
	/// \param	B		An other point of the lane, must be different from A. 
	/// \return	true if on right of the lane, false if not. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool isOnRightOfLane(const Vector2& point, const Vector2& A, const Vector2& B);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Project perpendiculary a point on a circle.
	///
	///			Compute the closest solution from the point.
	/// \param	point			The point to project. 
	/// \param	center			The circle center. 
	/// \param	radius			The circle radius. 
	/// \param [out]	result	The result. 
	///-------------------------------------------------------------------------------------------------
	STK_API void projectOnCircle(const Vector2& point, const Vector2& center, double radius, Vector2& result);

	///-------------------------------------------------------------------------------------------------
	/// \brief	Project a point on segment. 
	/// \param	point				The point to project. 
	/// \param	A1					The segment start. 
	/// \param	A2					The segment end. 
	/// \param	result				The result. 
	/// \param [out]	dist		The distance from A1 to result (contained in the interval : 0..segment length). 
	/// \return	true if it succeeds, false if it fails. 
	///-------------------------------------------------------------------------------------------------
	STK_API bool projectOnSegment(const Vector2& point, const Vector2& A1, const Vector2& A2, Vector2& result, double& dist);

	enum t_Signale { TTrapeze, TEnS, TExponentiel };
	//STKUTILS_API const char* t_SignaleToText(t_Signale t);

	STK_API double Signale(t_Signale type, double x);
	STK_API double Signale(t_Signale type, double y1, double y2, double x1, double x2, double x);

	///-------------------------------------------------------------------------------------------------
	/// \brief Calculate the discrete fourier transformation over the given sequence
	/// \param sequence			The sequence of pair (Real, Img) to transform
	///	\param [out] result		The result sequence of pair (Real, Img)
	///-------------------------------------------------------------------------------------------------
	typedef std::pair<double, double> TComplex;
	typedef std::vector<TComplex> TComplexSequence;
	STK_API void fastFourierTransform(const TComplexSequence &sequence, TComplexSequence &result, bool inverse=false);


	//R est un repere en mouvement
	//M fixe dans R
	//retourne la vitesse de M dans le repere globale
	STK_API stk::Vector3 VitesseEntrainement(
		double roulis, //orientation de R (devrait etre un "stk::Mark"...)
		double tang,
		double lacet,
		const stk::Vector3& M, //position de M dans R
		const stk::Vector3& W, //vecteur vitesse de rotation de R (dans le repere R)
		const stk::Vector3& VR); //vitesse de l'origine de R dans le repere globale


	STK_API stk::Vector3 VitesseEntrainement(const stk::Mark& R,	//le repere du solide (ex : vhc.Pos) par rapp au global
		const stk::Vector3& V,		//vecteur vitesse linéaire instantannée	dans le repere local (caisse)
		const stk::Vector3& W,		//vecteur vitesse rotation instantannée	dans le repere local (caisse)
		const stk::Vector3& M);		//position du point de mesure dans le repere local (caisse)


	//R est un repere en mouvement
	//M fixe dans R
	//retourne l'acceleration de M dans le repere globale
	STK_API stk::Vector3 AccelerationEntrainement(
		const stk::Mark& R,
		const stk::Vector3& GammaR, //l'acceleration de l'origine de R dans le repere R
		const stk::Vector3& W, //vecteur vitesse de rotation de R (dans le repere R!!)
		const stk::Vector3& dW, //la derivee du vecteur vitesse de rotation de R par rapport au temps (dans le repere R)
		const stk::Vector3& M);

}