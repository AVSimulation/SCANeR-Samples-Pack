#pragma once

#include "stk/Vector2.h"
	
namespace stk {
class STK_API Box2
{
	public:
		Box2();
		Box2( const stk::Vector2& min, const stk::Vector2& max );

		void add ( const stk::Vector2& v );

		inline stk::Vector2 center() const { return 0.5f * (mMin + mMax); }
		
		// standard point in bbox test
		bool isPointInside( const stk::Vector2& 	vertex, const bool	equalInside = true ) const;

		//! Intersecting test less stringent than inside test
		bool isInsideOrIntersecting( const stk::Box2& checkIfInsideBox ) const;
		//! Check if our bounding box contains the other one(checkIfInsideBox)
		bool isInsideOrTouching( const stk::Box2& checkIfInsideBox ) const;
		//! Check if the bounding boxes have common space
		bool isSharingSomeSpace( const stk::Box2& otherBox ) const;
		
		// see whether a box is valid or not
		inline bool isValid() const {return( !mIsEmpty ); }	
		inline void reset() {mIsEmpty=true; }

		// a degenerate side is one with 0 or negative length		
		inline bool		isSideDegenerate() const;
		inline int  	countDegenerateSides() const;
		
		// several degenerate but valid bboxes
		inline bool isPoint() const;
		inline bool isLine() const;
		inline bool isPlane() const;
		
		inline double getWidth() const; 	// in x
		inline double getHeight() const; 	// in y
			
		// both bounding boxes must be in the same coordinate system and axis aligned
		void setToIntersection( const stk::Box2& lhs, const stk::Box2& rhs );
		void setToUnion( const stk::Box2& lhs, const stk::Box2& rhs );

		// expand the bounding box about its centerpoint 1.5 = 150% of original dimensions		
		void scaleAboutCenter( const double scale );	
				
		// inset/outset a box - zero bound at minimum
		void inset( const double insetAmount );
		void outset( const double outsetAmount );
		void offset( const double offsetAmount );			
		
		//! returns true if the segment is inside or partly inside the bbox
		/*! point1: first point of the segment
			point2: second point of the segment
		*/
		bool isSegmentInside( const stk::Vector2& point1, const stk::Vector2& point2 ) const;
				
		
	public:	
		bool mIsEmpty;
		stk::Vector2 mMin;
		stk::Vector2 mMax;
};
}

bool stk::Box2::isPoint() const	{ return countDegenerateSides() == 2; }
bool stk::Box2::isLine() const	{ return countDegenerateSides() == 1; }
bool stk::Box2::isPlane() const	{ return countDegenerateSides() == 0; }
bool stk::Box2::isSideDegenerate() const { return (mMin.x >= mMax.x) || (mMin.y >= mMax.y); }
int  stk::Box2::countDegenerateSides() const { return ((mMin.x >= mMax.x)?1:0) + ((mMin.y >= mMax.y)?1:0); }
double stk::Box2::getWidth() const { return (isValid()) ? mMax.x - mMin.x : 0; }
double stk::Box2::getHeight() const	{ return (isValid()) ? mMax.y - mMin.y : 0; }

