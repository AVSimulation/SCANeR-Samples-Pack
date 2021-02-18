#include "ObjectBoundingBox2D.h"

#include "stk/Vector3.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Array>

//=============================================================================

ObjectBoundingBox2D::ObjectBoundingBox2D() :
	my2DBBoxGeode(NULL),
	my2DBBoxGeometry(NULL),
	my2DBBoxColor(NULL)
{
}

//=============================================================================

ObjectBoundingBox2D::~ObjectBoundingBox2D ()
{
}

//=============================================================================

void ObjectBoundingBox2D::setPixelCoords(const stk::Vector3& bottomLeft, const stk::Vector3& bottomRight, const stk::Vector3& topRight, const stk::Vector3& topLeft)
{
	osg::Vec3Array* verticesCoords = static_cast<osg::Vec3Array*>(my2DBBoxGeometry->getVertexArray());

	(*verticesCoords)[0].set(bottomLeft.x, bottomLeft.y, bottomLeft.z);
	(*verticesCoords)[1].set(bottomRight.x, bottomRight.y, bottomRight.z);
	(*verticesCoords)[2].set(topRight.x, topRight.y, topRight.z);
	(*verticesCoords)[3].set(topLeft.x, topLeft.y, topLeft.z);

	//update geometry bounding box for the frustum culling to work properly
	my2DBBoxGeometry->setInitialBound(my2DBBoxGeometry->computeBound());
}

//=============================================================================

void ObjectBoundingBox2D::create2DBoundingBox()
{
	int nbVertices = 4;

	//vertices coords
	osg::Vec3Array* verticesCoords = new osg::Vec3Array(nbVertices);
	for (int i = 0; i < nbVertices; i++)
		(*verticesCoords)[i].set(0.0, 0.0, 0.0);

	//vertices color
	my2DBBoxColor = new osg::Vec4Array(1);
	(*my2DBBoxColor)[0].set(0.0f, 0.0f, 0.0f, 1.0f);

	//box lines strip
	//osg::DrawElementsUInt* pPoints = new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_STRIP, 0);
	osg::DrawElementsUInt* pPoints = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	for (int i = 0; i < nbVertices; i++)
	{
		pPoints->push_back(i);
	}

	//the 2D bounding box geometry
	my2DBBoxGeometry = new osg::Geometry;
	my2DBBoxGeometry->setDataVariance(osg::Object::DYNAMIC);
	my2DBBoxGeometry->setUseDisplayList(false);
	my2DBBoxGeometry->setUseVertexBufferObjects(false);
	my2DBBoxGeometry->setVertexArray(verticesCoords);
	my2DBBoxGeometry->setColorArray(my2DBBoxColor);
	my2DBBoxGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	my2DBBoxGeometry->addPrimitiveSet(pPoints);

	//the 2D bounding geode
	my2DBBoxGeode = new osg::Geode;
	my2DBBoxGeode->setName("DEBUG_2D_BBOX_GEODE");
	my2DBBoxGeode->addDrawable(my2DBBoxGeometry);
}

//=============================================================================

void ObjectBoundingBox2D::setVisible(bool visible)
{
	if (my2DBBoxColor)
	{
		if (visible)
			(*my2DBBoxColor)[0].set(1.0f, 1.0f, 0.0f, 1.0f);
		else
			(*my2DBBoxColor)[0].set(0.4f, 0.4f, 0.4f, 1.0f);
	}
}
