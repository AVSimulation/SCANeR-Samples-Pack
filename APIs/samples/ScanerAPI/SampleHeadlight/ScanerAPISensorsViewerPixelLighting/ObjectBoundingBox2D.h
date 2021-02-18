#pragma once

#include <osg/Array>

namespace osg
{
	class Group;
	class Geode;
	class Geometry;
}
namespace stk
{
	class Vector3;
}


class ObjectBoundingBox2D
{
public:

	ObjectBoundingBox2D();

	virtual ~ObjectBoundingBox2D();

	/**
	 * Sets the coordinates of the bounding box min and max points in its parent sensor beam view.
	 * @param[in] bottomLeft the coord of the 2D bounding box bottom-left point, in normalized coordinates ([0..1] range)
	 * @param[in] bottomRight the coord of the 2D bounding box bottom-right point, in normalized coordinates ([0..1] range)
	 * @param[in] topRight the coord of the 2D bounding box top-right point, in normalized coordinates ([0..1] range)
	 * @param[in] topLeft the coord of the 2D bounding box top-left point, in normalized coordinates ([0..1] range)
	 */
	void setPixelCoords(const stk::Vector3& bottomLeft, const stk::Vector3& bottomRight, const stk::Vector3& topRight, const stk::Vector3& topLeft);

	/**
	 * Gets the 2D bounding box geode.
	 * @return the 2D bounding box geode.
	 */
	osg::Geode* get2DBoundingBoxGeode() const { return my2DBBoxGeode; };

	/**
	 * Sets the 2D bounding box debug geometry visible/not visible from its sensor beam parent view. This does not show/hide
	 * the geometry, but change its color to show that the bounding box is within the beam but hidden by other geometries.
	 * @param[in] visible the bounding box new visible status.
	 */
	void setVisible(bool visible);

	/**
	 * Creates the debug representation of the 2D bounding box.
	 */
	void create2DBoundingBox();

private:

	/** The 2D bounding box geode */
	osg::Geode* my2DBBoxGeode;

	/** The 2D bounding box geometry */
	osg::Geometry* my2DBBoxGeometry;

	/** The bounding box color */
	osg::Vec4Array* my2DBBoxColor;
};
