#include "Picto3D.h"

#include "stk/Transform.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/Depth>

#include <osgDB/ReadFile>

#include "scanerAPI/scanerAPI_DLL_C.h"

//=============================================================================

Picto3D::Picto3D() :
	my2DBBoxGeode(NULL),
	my2DBBoxGeometry(NULL),
	my2DBBoxColor(NULL),
	myTexture(NULL)
{
}

//=============================================================================

Picto3D::~Picto3D()
{
}

//=============================================================================

void Picto3D::setPixelCoords(int windowWidth, int windowHeight, const stk::Transform& vehicleToLightTransform, const stk::Transform& eyeToLightTransform, const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix)
{
	if (myTexture && my2DBBoxGeometry)
	{
		osg::Vec3Array* verticesCoords = static_cast<osg::Vec3Array*>(my2DBBoxGeometry->getVertexArray());

		//texture
		double windowRatio = (double)windowHeight / (double)windowWidth;
		double textureRatio = (double)myTexture->getTextureWidth() / (double)myTexture->getTextureHeight();

		if (true)
		{
			//for 3D display (world)
			double x = 6.0;
			double bottom = 0.0;
			double top = 0.6;

			//for 3D display (eye)
			x = 6.0;
			bottom = -0.5;
			top = -1.0;
			double height = (top - bottom);
			double width = (height * textureRatio);
			double left = -(width / 2.0);
			double right = (width / 2.0);

			//stk::Vector3 bottomLeftInVehSTK (x, left, bottom);
			stk::Vector3 bottomLeftInVehSTK (5.0, 1.0, -1.25);
			stk::Vector3 bottomLeftInLightSTK = eyeToLightTransform.apply(bottomLeftInVehSTK);
			osg::Vec3 bottomLeftInLight(bottomLeftInLightSTK.x, bottomLeftInLightSTK.y, bottomLeftInLightSTK.z);
			osg::Vec4 bottomLeftProj;
			project(bottomLeftInLight, viewMatrix, projectionMatrix, bottomLeftProj);

			//stk::Vector3 bottomRightInVehSTK(x, right, bottom);
			stk::Vector3 bottomRightInVehSTK(5.0, -1.0, -1.25);
			stk::Vector3 bottomRightInLightSTK = eyeToLightTransform.apply(bottomRightInVehSTK);
			osg::Vec3 bottomRightInLight(bottomRightInLightSTK.x, bottomRightInLightSTK.y, bottomRightInLightSTK.z);
			osg::Vec4 bottomRightProj;
			project(bottomRightInLight, viewMatrix, projectionMatrix, bottomRightProj);

			//stk::Vector3 topRightInVehSTK(x, right, top);
			stk::Vector3 topRightInVehSTK(20.0, -1.0, -1.25);
			stk::Vector3 topRightInLightSTK = eyeToLightTransform.apply(topRightInVehSTK);
			osg::Vec3 topRightInLight(topRightInLightSTK.x, topRightInLightSTK.y, topRightInLightSTK.z);
			osg::Vec4 topRightProj;
			project(topRightInLight, viewMatrix, projectionMatrix, topRightProj);

			//stk::Vector3 topLeftInVehSTK(x, left, top);
			stk::Vector3 topLeftInVehSTK(20.0, 1.0, -1.25);
			stk::Vector3 topLeftInLightSTK = eyeToLightTransform.apply(topLeftInVehSTK);
			osg::Vec3 topLeftInLight(topLeftInLightSTK.x, topLeftInLightSTK.y, topLeftInLightSTK.z);
			osg::Vec4 topLeftProj;
			project(topLeftInLight, viewMatrix, projectionMatrix, topLeftProj);

			//values are in [-1..1] range : go to [0..1] range
			bottomLeftProj = (bottomLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
			bottomRightProj = (bottomRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
			topRightProj = (topRightProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);
			topLeftProj = (topLeftProj / 2.0) + osg::Vec4(0.5, 0.5, 0.5, 0.5);

			//2D box visual representation
			(*verticesCoords)[0].set(bottomLeftProj.x(), bottomLeftProj.y(), bottomLeftProj.z());
			(*verticesCoords)[1].set(bottomRightProj.x(), bottomRightProj.y(), bottomRightProj.z());
			(*verticesCoords)[2].set(topRightProj.x(), topRightProj.y(), topRightProj.z());
			(*verticesCoords)[3].set(topLeftProj.x(), topLeftProj.y(), topLeftProj.z());

			//2D box visual representation
			/*(*verticesCoords)[0].set(bottomLeftInLight);
			(*verticesCoords)[1].set(bottomRightInLight);
			(*verticesCoords)[2].set(topRightInLight);
			(*verticesCoords)[3].set(topLeftInLight);*/

			/*(*textureCoords)[0].set(0.0, 0.0, 0.0, 1.0);
			(*textureCoords)[1].set(bottomRightProj.y(), 0.0, 0.0, bottomRightProj.y());
			(*textureCoords)[2].set(bottomRightProj.y(), bottomRightProj.x(), 0.0, 1.0);
			(*textureCoords)[3].set(0.0, bottomRightProj.x(), 0.0, 1.0);*/
		}

		//compute image position on screen
		if (false)
		{
			//for 2D display
			double bottom = 0.2;
			double top = 0.45;
			double height = (top - bottom);
			double width = (height * textureRatio * windowRatio);
			double left = 0.5 - (width / 2.0);
			double right = 0.5 + (width / 2.0);

			osg::Vec3 bottomLeft(left, bottom, 0.0);
			osg::Vec3 bottomRight(right, bottom, 0.0);
			osg::Vec3 topRight(right, top, 0.0);
			osg::Vec3 topLeft(left, top, 0.0);

			(*verticesCoords)[0].set(left, bottom, 0.0);
			(*verticesCoords)[1].set(right, bottom, 0.0);
			(*verticesCoords)[2].set(right, top - height / 3.0, 0.0);
			(*verticesCoords)[3].set(left, top - height / 3.0, 0.0);
		}

		/***********
		//inverse projection for anamorphose
		osg::Matrix viewProjectionMatrix;
		viewProjectionMatrix.makeFrustum(
		-0.7002,
		0.7002,
		-0.3939,
		0.3939,
		1.0,
		1000);
		osg::Matrix inverseProjectionMatrix = osg::Matrix::inverse(viewProjectionMatrix);
		double ndcBottom = -0.8;
		double ndcTop = -0.2;
		double ndcWidth = ((ndcTop - ndcBottom) * textureRatio * windowRatio);
		double ndcLeft = 0.0 - (ndcWidth / 2.0);
		double ndcRight = 0.0 + (ndcWidth / 2.0);
		osg::Vec3 ndcBottomLeft(left, bottom, 0.0);
		osg::Vec3 ndcBottomRight(right, bottom, 0.0);
		osg::Vec3 ndcTopRight(right, top, 0.0);
		osg::Vec3 ndcTopLeft(left, top, 0.0);
		osg::Vec3 bottomLeftProj = inverseProjectionMatrix.preMult(ndcBottomLeft);
		osg::Vec3 bottomRightProj = inverseProjectionMatrix.preMult(ndcBottomRight);
		osg::Vec3 topRightProj = inverseProjectionMatrix.preMult(ndcTopRight);
		osg::Vec3 topLeftProj = inverseProjectionMatrix.preMult(ndcTopLeft);
		***********/

		/*****
		osg::Vec3 bottomLeftProj (3.0, 2.0, -0.8);
		osg::Vec3 bottomRightProj (3.0, -2.0, -0.8);
		osg::Vec3 topRightProj (20.0, -3.0, 0.8);
		osg::Vec3 topLeftProj (20.0, 3.0, 0.8);

		(*verticesCoords)[0].set(bottomLeftProj);
		(*verticesCoords)[1].set(bottomRightProj);
		(*verticesCoords)[2].set(topRightProj);
		(*verticesCoords)[3].set(topLeftProj);
		*****/

		//update geometry bounding box for the frustum culling to work properly
		my2DBBoxGeometry->setInitialBound(my2DBBoxGeometry->computeBoundingBox());
	}
}

//=============================================================================

void Picto3D::project(const osg::Vec3 &pointToProject, const osg::Matrix& viewMatrix, const osg::Matrix &projectionMatrix, osg::Vec4 &projectedPoint)
{
	double left = 0.0, right = 0.0, bottom = 0.0, top = 0.0, zNear = 0.0, zFar = 0.0;
	projectionMatrix.getFrustum(left, right, bottom, top, zNear, zFar);

	//world space bounding box
	osg::Vec4 pointInWorld(pointToProject.x(), pointToProject.y(), pointToProject.z(), 1.0);

	//eye space bounding box
	osg::Vec4 pointInCamera = viewMatrix.preMult(pointInWorld);

	//vec3 eye space bounding box
	osg::Vec3 pointInCamera3(pointInCamera.x(), pointInCamera.y(), pointInCamera.z());

	//proj space clipping bounding box
	osg::Vec4 pointProjSpaceClip = projectionMatrix.preMult(pointInCamera);

	//proj space bounding box
	projectedPoint.set(pointProjSpaceClip.x() / pointProjSpaceClip.w(), pointProjSpaceClip.y() / pointProjSpaceClip.w(), pointProjSpaceClip.z() / pointProjSpaceClip.w(), 1.0);
}

//=============================================================================

void Picto3D::updateMinMaxCoords(const osg::Vec4& point, double& xMin, double& xMax, double& yMin, double& yMax) const
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

void Picto3D::createGeode()
{
	int nbVertices = 4;

	//vertices coords
	osg::Vec3Array* verticesCoords = new osg::Vec3Array(nbVertices);
	for (int i = 0; i < nbVertices; i++)
	{
		(*verticesCoords)[i].set(0.0, 0.0, 0.0);
	}

	//vertices color
	my2DBBoxColor = new osg::Vec4Array(1);
	(*my2DBBoxColor)[0].set(1.0f, 1.0f, 1.0f, 1.0f);

	//texture coords array
	osg::Vec2Array* texCoords = new osg::Vec2Array(nbVertices);
	(*texCoords)[0].set(0.0, 0.0);
	(*texCoords)[1].set(1.0, 0.0);
	(*texCoords)[2].set(1.0, 1.0);
	(*texCoords)[3].set(0.0, 1.0);

	//box lines strip
	///osg::DrawElementsUInt* pPoints = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	osg::DrawElementsUInt* pPoints = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	/*for (int i = 0; i < nbVertices; i++)
	{
		pPoints->push_back(i);
	}*/
	pPoints->push_back(0);
	pPoints->push_back(1);
	pPoints->push_back(2);
	pPoints->push_back(0);
	pPoints->push_back(2);
	pPoints->push_back(3);

	//the 2D bounding box geometry
	my2DBBoxGeometry = new osg::Geometry;
	my2DBBoxGeometry->setDataVariance(osg::Object::DYNAMIC);
	my2DBBoxGeometry->setUseDisplayList(false);
	my2DBBoxGeometry->setUseVertexBufferObjects(false);
	my2DBBoxGeometry->setVertexArray(verticesCoords);
	my2DBBoxGeometry->setTexCoordArray(0, texCoords);
	my2DBBoxGeometry->setColorArray(my2DBBoxColor);
	my2DBBoxGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	my2DBBoxGeometry->addPrimitiveSet(pPoints);

	//the 2D bounding geode
	my2DBBoxGeode = new osg::Geode;
	my2DBBoxGeode->setName("DEBUG_2D_BBOX_GEODE");
	my2DBBoxGeode->addDrawable(my2DBBoxGeometry);
	osg::StateSet* stateSet = my2DBBoxGeode->getOrCreateStateSet();

	//texture
	osg::Image* image = osgDB::readImageFile(Utils_getPath("data\\images\\2048px-France_road_sign_A13b_NB.png"));
	if (image)
	{
		myTexture = new osg::Texture2D();
		myTexture->setUseHardwareMipMapGeneration(true);
		myTexture->setImage(image);
		myTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		myTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		myTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER);
		myTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER);
		myTexture->setResizeNonPowerOfTwoHint(false);
		myTexture->setInternalFormat(GL_RGBA8);
		myTexture->setTextureWidth(image->s());
		myTexture->setTextureHeight(image->t());
		myTexture->setUnRefImageDataAfterApply(true);
		myTexture->setMaxAnisotropy(16);
		stateSet->setTextureAttributeAndModes(0, myTexture, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	}
	stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateSet->setMode(GL_CULL_FACE, osg::StateAttribute::ON);
	stateSet->setAttributeAndModes(new osg::Depth(osg::Depth::ALWAYS,0.0,1.0,false));
	stateSet->setRenderBinDetails(20, "RenderBin");

	my2DBBoxGeometry->setInitialBound(my2DBBoxGeometry->computeBoundingBox());
}
