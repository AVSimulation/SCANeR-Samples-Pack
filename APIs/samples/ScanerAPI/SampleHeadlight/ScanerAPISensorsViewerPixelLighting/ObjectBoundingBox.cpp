#include "ObjectBoundingBox.h"

#include "stk/Unit.h"
#include "stk/Vector2.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Projection>
#include <osg/MatrixTransform>
#include <osg/CullFace>
#include <osg/Point>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>

//=============================================================================

ObjectBoundingBox::ObjectBoundingBox() :
	myNbVertices(8),
	myDebugDetectionPointsGeode (NULL),
	my3DBBoxGeometry (NULL),
	my3DBBoxVerticesCoords(NULL),
	my3DBBoxVerticesColors(NULL),
	my2DBox()
{
}

//=============================================================================

ObjectBoundingBox::~ObjectBoundingBox ()
{
}

//=============================================================================

void ObjectBoundingBox::updatePoints(
	const stk::Vector3 &rearBottomRight,
	const stk::Vector3 &rearTopRight,
	const stk::Vector3 &rearbottomLeft,
	const stk::Vector3 &rearTopLeft,
	const stk::Vector3 &frontBottomRight,
	const stk::Vector3 &frontTopRight,
	const stk::Vector3 &frontbottomLeft,
	const stk::Vector3 &frontTopLeft)
{
	if (my3DBBoxVerticesCoords)
	{
		(*my3DBBoxVerticesCoords)[0].set(rearBottomRight.x, rearBottomRight.y, rearBottomRight.z);
		(*my3DBBoxVerticesCoords)[1].set(rearTopRight.x, rearTopRight.y, rearTopRight.z);
		(*my3DBBoxVerticesCoords)[2].set(rearbottomLeft.x, rearbottomLeft.y, rearbottomLeft.z);
		(*my3DBBoxVerticesCoords)[3].set(rearTopLeft.x, rearTopLeft.y, rearTopLeft.z);
		(*my3DBBoxVerticesCoords)[4].set(frontBottomRight.x, frontBottomRight.y, frontBottomRight.z);
		(*my3DBBoxVerticesCoords)[5].set(frontTopRight.x, frontTopRight.y, frontTopRight.z);
		(*my3DBBoxVerticesCoords)[6].set(frontbottomLeft.x, frontbottomLeft.y, frontbottomLeft.z);
		(*my3DBBoxVerticesCoords)[7].set(frontTopLeft.x, frontTopLeft.y, frontTopLeft.z);
	}

	//update geometry bounding box for the frustum culling to work properly
	if (my3DBBoxGeometry)
		my3DBBoxGeometry->setInitialBound(my3DBBoxGeometry->computeBoundingBox());
}

//=============================================================================

void ObjectBoundingBox::project(const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix)
{
	double left = 0.0, right = 0.0, bottom = 0.0, top = 0.0, zNear = 0.0, zFar = 0.0;
	projectionMatrix.getFrustum(left, right, bottom, top, zNear, zFar);

	//compute the bounding box visible faces

	//world space bounding box
	osg::Vec4 rearBottomRightWorld((*my3DBBoxVerticesCoords)[0].x(), (*my3DBBoxVerticesCoords)[0].y(), (*my3DBBoxVerticesCoords)[0].z(), 1.0);
	osg::Vec4 rearTopRightWorld((*my3DBBoxVerticesCoords)[1].x(), (*my3DBBoxVerticesCoords)[1].y(), (*my3DBBoxVerticesCoords)[1].z(), 1.0);
	osg::Vec4 rearBottomLeftWorld((*my3DBBoxVerticesCoords)[2].x(), (*my3DBBoxVerticesCoords)[2].y(), (*my3DBBoxVerticesCoords)[2].z(), 1.0);
	osg::Vec4 rearTopLeftWorld((*my3DBBoxVerticesCoords)[3].x(), (*my3DBBoxVerticesCoords)[3].y(), (*my3DBBoxVerticesCoords)[3].z(), 1.0);
	osg::Vec4 frontBottomRightWorld((*my3DBBoxVerticesCoords)[4].x(), (*my3DBBoxVerticesCoords)[4].y(), (*my3DBBoxVerticesCoords)[4].z(), 1.0);
	osg::Vec4 frontTopRightWorld((*my3DBBoxVerticesCoords)[5].x(), (*my3DBBoxVerticesCoords)[5].y(), (*my3DBBoxVerticesCoords)[5].z(), 1.0);
	osg::Vec4 frontBottomLeftWorld((*my3DBBoxVerticesCoords)[6].x(), (*my3DBBoxVerticesCoords)[6].y(), (*my3DBBoxVerticesCoords)[6].z(), 1.0);
	osg::Vec4 frontTopLeftWorld((*my3DBBoxVerticesCoords)[7].x(), (*my3DBBoxVerticesCoords)[7].y(), (*my3DBBoxVerticesCoords)[7].z(), 1.0);

	//eye space bounding box
	osg::Vec4 rearBottomRightEye = viewMatrix.preMult(rearBottomRightWorld);
	osg::Vec4 rearTopRightEye = viewMatrix.preMult(rearTopRightWorld);
	osg::Vec4 rearBottomLeftEye = viewMatrix.preMult(rearBottomLeftWorld);
	osg::Vec4 rearTopLeftEye = viewMatrix.preMult(rearTopLeftWorld);
	osg::Vec4 frontBottomRightEye = viewMatrix.preMult(frontBottomRightWorld);
	osg::Vec4 frontTopRightEye = viewMatrix.preMult(frontTopRightWorld);
	osg::Vec4 frontBottomLeftEye = viewMatrix.preMult(frontBottomLeftWorld);
	osg::Vec4 frontTopLeftEye = viewMatrix.preMult(frontTopLeftWorld);
	if (frontBottomRightEye.z() > 0.0) frontBottomRightEye.set(frontBottomRightEye.x(), frontBottomRightEye.y(), -zNear, frontBottomRightEye.w());
	if (frontTopRightEye.z() > 0.0) frontTopRightEye.set(frontTopRightEye.x(), frontTopRightEye.y(), -zNear, frontTopRightEye.w());
	if (frontBottomLeftEye.z() > 0.0)frontBottomLeftEye.set(frontBottomLeftEye.x(), frontBottomLeftEye.y(), -zNear, frontBottomLeftEye.w());
	if (frontTopLeftEye.z() > 0.0) frontTopLeftEye.set(frontTopLeftEye.x(), frontTopLeftEye.y(), -zNear, frontTopLeftEye.w());

	//proj space clipping bounding box
	osg::Vec4 rearBottomRightProjSpaceClip = projectionMatrix.preMult(rearBottomRightEye);
	osg::Vec4 rearTopRightProjSpaceClip = projectionMatrix.preMult(rearTopRightEye);
	osg::Vec4 rearBottomLeftProjSpaceClip = projectionMatrix.preMult(rearBottomLeftEye);
	osg::Vec4 rearTopLeftProjSpaceClip = projectionMatrix.preMult(rearTopLeftEye);
	osg::Vec4 frontBottomRightProjSpaceClip = projectionMatrix.preMult(frontBottomRightEye);
	osg::Vec4 frontTopRightProjSpaceClip = projectionMatrix.preMult(frontTopRightEye);
	osg::Vec4 frontBottomLeftProjSpaceClip = projectionMatrix.preMult(frontBottomLeftEye);
	osg::Vec4 frontTopLeftProjSpaceClip = projectionMatrix.preMult(frontTopLeftEye);

	//proj space bounding box
	osg::Vec4 rearBottomRightProj(rearBottomRightProjSpaceClip.x() / rearBottomRightProjSpaceClip.w(), rearBottomRightProjSpaceClip.y() / rearBottomRightProjSpaceClip.w(), rearBottomRightProjSpaceClip.z() / rearBottomRightProjSpaceClip.w(), 1.0);
	osg::Vec4 rearTopRightProj(rearTopRightProjSpaceClip.x() / rearTopRightProjSpaceClip.w(), rearTopRightProjSpaceClip.y() / rearTopRightProjSpaceClip.w(), rearTopRightProjSpaceClip.z() / rearTopRightProjSpaceClip.w(), 1.0);
	osg::Vec4 rearBottomLeftProj(rearBottomLeftProjSpaceClip.x() / rearBottomLeftProjSpaceClip.w(), rearBottomLeftProjSpaceClip.y() / rearBottomLeftProjSpaceClip.w(), rearBottomLeftProjSpaceClip.z() / rearBottomLeftProjSpaceClip.w(), 1.0);
	osg::Vec4 rearTopLeftProj(rearTopLeftProjSpaceClip.x() / rearTopLeftProjSpaceClip.w(), rearTopLeftProjSpaceClip.y() / rearTopLeftProjSpaceClip.w(), rearTopLeftProjSpaceClip.z() / rearTopLeftProjSpaceClip.w(), 1.0);
	osg::Vec4 frontBottomRightProj(frontBottomRightProjSpaceClip.x() / frontBottomRightProjSpaceClip.w(), frontBottomRightProjSpaceClip.y() / frontBottomRightProjSpaceClip.w(), frontBottomRightProjSpaceClip.z() / frontBottomRightProjSpaceClip.w(), 1.0);
	osg::Vec4 frontTopRightProj(frontTopRightProjSpaceClip.x() / frontTopRightProjSpaceClip.w(), frontTopRightProjSpaceClip.y() / frontTopRightProjSpaceClip.w(), frontTopRightProjSpaceClip.z() / frontTopRightProjSpaceClip.w(), 1.0);
	osg::Vec4 frontBottomLeftProj(frontBottomLeftProjSpaceClip.x() / frontBottomLeftProjSpaceClip.w(), frontBottomLeftProjSpaceClip.y() / frontBottomLeftProjSpaceClip.w(), frontBottomLeftProjSpaceClip.z() / frontBottomLeftProjSpaceClip.w(), 1.0);
	osg::Vec4 frontTopLeftProj(frontTopLeftProjSpaceClip.x() / frontTopLeftProjSpaceClip.w(), frontTopLeftProjSpaceClip.y() / frontTopLeftProjSpaceClip.w(), frontTopLeftProjSpaceClip.z() / frontTopLeftProjSpaceClip.w(), 1.0);

	//values are in [-1..1] range : go to [0..1] range
	double xMin = 1000000.0;
	double xMax = -1000000.0;
	double yMin = 1000000.0;
	double yMax = -1000000.0;
	rearBottomRightProj = (rearBottomRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(rearBottomRightProj, xMin, xMax, yMin, yMax);
	rearTopRightProj = (rearTopRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(rearTopRightProj, xMin, xMax, yMin, yMax);
	rearBottomLeftProj = (rearBottomLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(rearBottomLeftProj, xMin, xMax, yMin, yMax);
	rearTopLeftProj = (rearTopLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(rearTopLeftProj, xMin, xMax, yMin, yMax);
	frontBottomRightProj = (frontBottomRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(frontBottomRightProj, xMin, xMax, yMin, yMax);
	frontTopRightProj = (frontTopRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(frontTopRightProj, xMin, xMax, yMin, yMax);
	frontBottomLeftProj = (frontBottomLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(frontBottomLeftProj, xMin, xMax, yMin, yMax);
	frontTopLeftProj = (frontTopLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
	updateMinMaxCoords(frontTopLeftProj, xMin, xMax, yMin, yMax);

	//2D box visual representation
	stk::Vector3 bottomLeft = stk::Vector3(xMin, yMin, 0.0);
	stk::Vector3 bottomRight = stk::Vector3(xMax, yMin, 0.0);
	stk::Vector3 topRight = stk::Vector3(xMax, yMax, 0.0);
	stk::Vector3 topLeft = stk::Vector3(xMin, yMax, 0.0);
	my2DBox.setPixelCoords(bottomLeft, bottomRight, topRight, topLeft);
}

//=============================================================================

void ObjectBoundingBox::updateMinMaxCoords(const osg::Vec4& point, double& xMin, double& xMax, double& yMin, double& yMax) const
{
	if (point.x() < xMin)
		xMin = point.x();
	if (point.x() > xMax)
		xMax = point.x();
	if (point.y() < yMin)
		yMin = point.y();
	if (point.y() > yMax)
		yMax = point.y();
}

//=============================================================================

void ObjectBoundingBox::create3DBoundingBox ()
{
	//vertices
	my3DBBoxVerticesCoords = new osg::Vec3Array(myNbVertices);
	for (int i = 0; i<myNbVertices; i++)
	{
		(*my3DBBoxVerticesCoords)[i].set (0.0, 0.0, 0.0);
	}

	//only 2D boxes for now
	return;

	//vertices color
	my3DBBoxVerticesColors = new osg::Vec4Array(myNbVertices);
	for (int i = 0; i<myNbVertices; i++)
	{
		(*my3DBBoxVerticesColors)[i].set (0.0, 0.0, 0.0, 1.0);
	}

	//points
	osg::DrawElementsUInt* pPoints = new osg::DrawElementsUInt(osg::PrimitiveSet::POINTS, 0);
	for (int i = 0; i<myNbVertices; i++)
	{
		pPoints->push_back (i);
	}

	//3D bounding box geometry
	if (my3DBBoxGeometry == NULL)
		my3DBBoxGeometry = new osg::Geometry;
	my3DBBoxGeometry->setDataVariance (osg::Object::DYNAMIC);
	my3DBBoxGeometry->setUseDisplayList (false);
	my3DBBoxGeometry->setUseVertexBufferObjects (false);
	my3DBBoxGeometry->setVertexArray (my3DBBoxVerticesCoords);
	my3DBBoxGeometry->setColorArray (my3DBBoxVerticesColors);
	my3DBBoxGeometry->setColorBinding (osg::Geometry::BIND_PER_VERTEX);
	my3DBBoxGeometry->addPrimitiveSet (pPoints);
	my3DBBoxGeometry->setInitialBound (my3DBBoxGeometry->computeBoundingBox());

	if (myDebugDetectionPointsGeode == NULL)
	{
		myDebugDetectionPointsGeode = new osg::Geode;
		myDebugDetectionPointsGeode->setName("DEBUG_3D_BBOX_GEODE");
	}
	else
		myDebugDetectionPointsGeode->removeDrawables(0, myDebugDetectionPointsGeode->getNumDrawables());
	myDebugDetectionPointsGeode->addDrawable (my3DBBoxGeometry);

	//state attributes
	osg::Point* pPoint = new osg::Point (1.0f);
	myDebugDetectionPointsGeode->getOrCreateStateSet()->setAttributeAndModes (pPoint, osg::StateAttribute::ON);
	myDebugDetectionPointsGeode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::OFF);
	myDebugDetectionPointsGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
}

//=============================================================================

void ObjectBoundingBox::create2DBoundingBox()
{
	my2DBox.create2DBoundingBox();
}

//=============================================================================

osg::Geode* ObjectBoundingBox::get2DBoundingBoxDebugRep() const
{
	return my2DBox.get2DBoundingBoxGeode();
}

//=============================================================================

void ObjectBoundingBox::hide()
{
	if (myDebugDetectionPointsGeode)
		myDebugDetectionPointsGeode->setNodeMask(0x0);
	my2DBox.get2DBoundingBoxGeode()->setNodeMask(0x0);
}

//=============================================================================

void ObjectBoundingBox::show()
{
	if (myDebugDetectionPointsGeode)
		myDebugDetectionPointsGeode->setNodeMask(0xffffffff);
	my2DBox.get2DBoundingBoxGeode()->setNodeMask(0xffffffff);
}
