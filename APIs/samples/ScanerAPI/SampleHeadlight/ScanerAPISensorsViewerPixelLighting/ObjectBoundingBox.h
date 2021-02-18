#pragma once

#include "ObjectBoundingBox2D.h"

#include <osg/Array>

#include <map>

namespace osg
{
	class Group;
	class Geode;
	class Geometry;
}

class ObjectBoundingBox
{
public:

	typedef enum
	{
		BBox_Mobile = 0,
		BBox_Infra = 1
	} BBoxType;

	ObjectBoundingBox();

	virtual ~ObjectBoundingBox();

	/**
	 * Create the 3D representation of the bounding box
	 */
	void create3DBoundingBox();

	/**
	 * @return the 3D representation of the bounding box.
	 */
	osg::Geode* get3DBoundingBoxDebugRep() const { return myDebugDetectionPointsGeode; };

	/**
	 * Create the 2D representation of the bounding box
	 */
	void create2DBoundingBox();

	/**
	 * @return the 2D representation of the bounding box.
	 */
	osg::Geode* get2DBoundingBoxDebugRep() const;

	/**
	 * Update the 8 points of the 3D representation of the bounding box;
	 */
	void updatePoints(
		const stk::Vector3 &rearBottomRight,
		const stk::Vector3 &rearTopRight,
		const stk::Vector3 &rearbottomLeft,
		const stk::Vector3 &rearTopLeft,
		const stk::Vector3 &frontBottomRight,
		const stk::Vector3 &frontTopRight,
		const stk::Vector3 &frontbottomLeft,
		const stk::Vector3 &frontTopLeft);

	/**
	 * Project the bounding box points on the viewer image plane to get the pixel coordinates of the box 2D corners.
	 * @param[in] viewMatrix the viewer OpenGL view matrix.
	 * @param[in] projectionMatrix the viewer OpenGL projection matrix.
	 */
	void project(const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix);

	/**
	 * @return the information about the 2D representation of the bounding box.
	 */
	const ObjectBoundingBox2D& get2DBoundingBox() const { return my2DBox; };

	/**
	 * Hide the 3D and 2D representations of the bounding box in the parent osg viewer.
	 */
	void hide();

	/**
	 * Show the 3D and 2D representations of the bounding box in the parent osg viewer.
	 */
	void show();

private:

	void updateMinMaxCoords(const osg::Vec4& point, double& xMin, double& xMax, double& yMin, double& yMax) const;

private:

	int myNbVertices;

	osg::Geode* myDebugDetectionPointsGeode;

	osg::Geometry* my3DBBoxGeometry;

	osg::Vec3Array* my3DBBoxVerticesCoords;

	osg::Vec4Array* my3DBBoxVerticesColors;

	ObjectBoundingBox2D my2DBox;
};
