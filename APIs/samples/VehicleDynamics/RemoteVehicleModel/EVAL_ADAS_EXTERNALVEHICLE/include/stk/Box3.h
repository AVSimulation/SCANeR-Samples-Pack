#pragma once

#include "stk/Vector3.h"
#include "stk/Vector2.h"

#include <vector>

namespace stk 
{
	class STK_API Box3
	{
	public:
		Box3();
		Box3(const Vector3& min, const Vector3& max);

		void add(const Vector3 &p);
		bool contains(const Vector3 &p) const;
		bool contains(const Vector2 &p) const;
		bool intersects(const Box3 &b2) const;

		Vector3 upperLeftCorner() const;
		Vector3 bottomLeftCorner() const;
		Vector3 upperRightCorner() const;
		Vector3 bottomRightCorner() const;

		Vector3 center() const;
		bool	circleContains(const Vector2 &p) const;
		double  radius() const;

		double	minDist(const Vector2 &pos) const;
		double	maxDist(const Vector2 &pos) const;

		double  centerDist(const Vector2 &pos) const;
		double  minCircleDist(const Vector2 &pos) const;
		double  maxCircleDist(const Vector2 &pos) const;

		Vector3 farestCorner(const Vector2 & pos) const;
		Vector3 nearestCorner(const Vector2 & pos) const;

		bool isValid() const {return !isEmpty;}
		void reset() {isEmpty = true;}

		void retrieveVertexList(std::vector<stk::Vector3>& vertexList) const;
		void retrieveFaceCenterList(std::vector<stk::Vector3>& vertexList) const;

		void setToIntersection( const Box3& lhs, const Box3& rhs );
		void setToUnion(const Box3& lhs, const Box3& rhs );

		inline double getWidth() const { return (isValid()) ? myMax.x - myMin.x : 0; }
		inline double getHeight() const { return (isValid()) ? myMax.y - myMin.y : 0; }
		inline double getDepth() const { return (isValid()) ? myMax.z - myMin.z : 0; }

		void inset( double insetAmount );
		void outset(double outsetAmount);
		void offset(double offsetAmount);
		void scaleAboutCenter(double scale);

	protected:

		void checkValidity();

	public:
		bool isEmpty;
		Vector3 myMin;
		Vector3 myMax;


	};
}