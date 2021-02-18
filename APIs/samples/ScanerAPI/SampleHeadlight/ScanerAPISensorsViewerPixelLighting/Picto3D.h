#pragma once

#include <osg/Array>

namespace osg
{
	class Group;
	class Geode;
	class Geometry;
	class Texture2D;
}

namespace stk
{
	class Transform;
}

class Picto3D
{
public:

	Picto3D();

	virtual ~Picto3D();

	/**
	 * Sets the coordinates of the bounding box min and max points in its parent sensor beam view.
	 * @param[in] bottomLeft the coord of the 2D bounding box bottom-left point, in normalized coordinates ([0..1] range)
	 * @param[in] bottomRight the coord of the 2D bounding box bottom-right point, in normalized coordinates ([0..1] range)
	 * @param[in] topRight the coord of the 2D bounding box top-right point, in normalized coordinates ([0..1] range)
	 * @param[in] topLeft the coord of the 2D bounding box top-left point, in normalized coordinates ([0..1] range)
	 */
	void setPixelCoords(int windowWidth, int windowHeight, const stk::Transform& vehicleToLightTransform, const stk::Transform& eyeToLightTransform, const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix);

	/**
	 * Gets the 2D bounding box geode.
	 * @return the 2D bounding box geode.
	 */
	osg::Geode* getGeode() const { return my2DBBoxGeode; };

	/**
	 * Creates the debug representation of the 2D bounding box.
	 */
	void createGeode();

private:

	void project(const osg::Vec3 &pointToProject, const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix, osg::Vec4 &projectedPoint);
	void updateMinMaxCoords(const osg::Vec4& point, double& xMin, double& xMax, double& yMin, double& yMax) const;

private:

	/** The 2D bounding box geode */
	osg::Geode* my2DBBoxGeode;

	/** The 2D bounding box geometry */
	osg::Geometry* my2DBBoxGeometry;

	/** The bounding box color */
	osg::Vec4Array* my2DBBoxColor;

	/** The bounding box color */
	osg::Texture2D* myTexture;
};
