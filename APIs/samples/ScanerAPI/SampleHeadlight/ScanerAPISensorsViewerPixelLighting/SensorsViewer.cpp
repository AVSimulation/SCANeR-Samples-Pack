#include "SensorsViewer.h"

#include "stk/Unit.h"
#include "stk/Transform.h"

#include <osg/Group>
#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osg/LineWidth>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/CompositeViewer>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>

#include <osgDB/ReadFile>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

//=============================================================================

//class SwitchOffVSyncOperation : public osg::Operation
//{
//public:
//	SwitchOffVSyncOperation() :
//		osg::Operation("SwitchOffVSyncOperation", false)
//#ifdef WIN32
//		, wglSwapIntervalEXT(NULL)
//#else
//		, glXSwapIntervalEXT(NULL)
//#endif
//	{}
//
//	virtual void operator () (osg::Object* object)
//	{
//#ifdef WIN32
//		if (!wglSwapIntervalEXT)
//			wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
//
//		if (wglSwapIntervalEXT)
//			wglSwapIntervalEXT(0);
//		else
//			std::cerr << "wglSwapIntervalEXT extention not supported!" << std::endl;
//#else
//		if (!glXSwapIntervalEXT)
//			glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((GLubyte*)"glXSwapIntervalEXT");
//
//		if(glXSwapIntervalEXT)
//		{
//			Display *d = glXGetCurrentDisplay();
//			glXSwapIntervalEXT( d, glXGetCurrentDrawable(), 0);
//		}
//		else
//			std::cerr << "glXSwapIntervalEXT extention not supported!" << std::endl;
//#endif
//	}
//#ifdef WIN32
//	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
//#else
//	PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;
//#endif
//};

//=============================================================================

SensorsViewer::SensorsViewer(const std::string& procName, int viewerWidth, int viewerHeight) :
myProcName(procName),
myGC(),
myCompositeViewer(nullptr),
myView(nullptr),
myWidth(viewerWidth),
myHeight(viewerHeight),
myVehicleEyePosition(),
myEyeToLightTransform(),
myVehicleToLightTransform(),
myRoot(nullptr),
my3DScene(nullptr),
my2DScene(nullptr),
myPicto3D(),
myOpenGLToSensorTransform(),
myMobilesBBoxes(),
myInfraBBoxes()
{
	//world to opengl
	myOpenGLToSensorTransform.localToGlobal(
		stk::convToSI(stk::TUnitDegre, 90.0),
		0.0,
		stk::convToSI(stk::TUnitDegre, -90.0), stk::Vector3(0, 0, 0));

	load();
}

//=============================================================================

SensorsViewer::~SensorsViewer()
{
	unload();
}

//=============================================================================

void SensorsViewer::load ()
{
	osg::Vec4f clearColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (!myCompositeViewer)
	{
		//create and configure the viewer
		myCompositeViewer = new osgViewer::CompositeViewer();

		//graphical context
		osg::GraphicsContext::Traits* traits = new osg::GraphicsContext::Traits;
		traits->x = 50;
		traits->y = 100;
		traits->width = myWidth;
		traits->height = myHeight;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		traits->vsync = false;
		traits->windowDecoration = true;
		traits->windowName = myProcName;
		myGC = osg::GraphicsContext::createGraphicsContext(traits);
		myGC->setClearColor(clearColor);
		myGC->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//create the sensor view
	myView = new osgViewer::View;
	myView->setName("Sensor view");
	myView->addEventHandler(new osgViewer::WindowSizeHandler);
	myView->addEventHandler(new osgViewer::StatsHandler);
	myView->addEventHandler(new osgViewer::HelpHandler);
	myView->addEventHandler(new osgViewer::ThreadingHandler);
	myView->addEventHandler(new osgGA::StateSetManipulator(myView->getCamera()->getOrCreateStateSet()));
	myCompositeViewer->addView(myView);

	//configure camera
	osg::Camera* camera = myView->getCamera();
	camera->setGraphicsContext(myGC);
	camera->setViewport(0, 0, myWidth, myHeight);
	camera->setProjectionResizePolicy(osg::Camera::FIXED);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
	camera->setCullingMode(osg::CullSettings::DEFAULT_CULLING | osg::CullSettings::VIEW_FRUSTUM_CULLING);
	camera->setClearColor(clearColor);

	//viewer FOV (radians)
	double hFOV = 119.069;
	double vFOV = 43.603;
	double leftDeg = -hFOV / 2.0; //-45.0
	double rightDeg = hFOV / 2.0; //45.0
	double bottomDeg = -vFOV / 2.0; //-20.0
	double topDeg = vFOV / 2.0; //20.0

	double left = stk::convToSI(stk::TUnitDegre, leftDeg);
	double right = stk::convToSI(stk::TUnitDegre, rightDeg);
	double bottom = stk::convToSI(stk::TUnitDegre, bottomDeg);
	double top = stk::convToSI(stk::TUnitDegre, topDeg);
	double zNear = 0.1;
	double zFar = 1000.0;
	camera->setProjectionMatrixAsFrustum(
		zNear * tan(left),
		zNear * tan(right),
		zNear * tan(bottom),
		zNear * tan(top),
		zNear,
		zFar);

	//viewer
	myRoot = new osg::Group;
	myRoot->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::OFF);
	myRoot->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	//init 3D scene
	{
		my3DScene = new osg::Group;
		myView->setSceneData(myRoot);
		myRoot->addChild(my3DScene);
	}

	//init 2D scene
	{
		//the 2D projection node
		osg::Projection* projection2D = new osg::Projection;
		projection2D->setDataVariance(osg::Object::STATIC);
		projection2D->setMatrix(osg::Matrix::ortho(0, 1, 0, 1, -1, 1));
		projection2D->getOrCreateStateSet()->setRenderBinDetails(10, "RenderBin");
		myRoot->addChild(projection2D);

		//the absolute position matrix
		osg::MatrixTransform* matrix2D = new osg::MatrixTransform;
		matrix2D->setDataVariance(osg::Object::STATIC);
		matrix2D->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		matrix2D->setMatrix(osg::Matrix::identity());
		projection2D->addChild(matrix2D);

		my2DScene = new osg::Group;
		my2DScene->setDataVariance(osg::Object::STATIC);
		matrix2D->addChild(my2DScene);
		myRoot->addChild(my2DScene);
	}

	myPicto3D.createGeode();
	//myPicto3D.setPixelCoords(myWidth, myHeight, myVehicleToLightTransform, camera->getViewMatrix(), camera->getProjectionMatrix());
	my2DScene->addChild(myPicto3D.getGeode());
	myPicto3D.getGeode()->setNodeMask(0x0);

	//myCompositeViewer->setRealizeOperation(new SwitchOffVSyncOperation());
	myCompositeViewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

	myCompositeViewer->realize();
	myCompositeViewer->startThreading();
}

//=============================================================================

void SensorsViewer::unload ()
{
	if (myCompositeViewer)
	{
		myCompositeViewer->stopThreading();

		while (myCompositeViewer->getNumViews() > 0)
		{
			osgViewer::View* view = myCompositeViewer->getView(0);
			myCompositeViewer->removeView(view);
		}

		//GL context must be explicitly closed after removing the views for the pbuffer mode to work properly
		myGC->close();

	}
	clear();
}

//=============================================================================

void SensorsViewer::update ()
{
	//view matrix
	stk::Transform viewTransf = myOpenGLToSensorTransform;

	//update view camera matrix
	osg::Camera* camera = myView->getCamera();
	osg::Matrix viewMatrix = camera->getViewMatrix();
	viewMatrix.set(
		viewTransf(0, 0), viewTransf(1, 0), viewTransf(2, 0), viewTransf(3, 0),
		viewTransf(0, 1), viewTransf(1, 1), viewTransf(2, 1), viewTransf(3, 1),
		viewTransf(0, 2), viewTransf(1, 2), viewTransf(2, 2), viewTransf(3, 2),
		viewTransf(0, 3), viewTransf(1, 3), viewTransf(2, 3), viewTransf(3, 3));
	camera->setViewMatrix(osg::Matrix::inverse(viewMatrix));

	myCompositeViewer->frame();
}

//=============================================================================

void SensorsViewer::setVehicleEyePosition(const stk::Vector3& eyePosition)
{
	myVehicleEyePosition = eyePosition;
};

//=============================================================================

void SensorsViewer::updateLightSourcePosition(const stk::Mark& lightPosition)
{
	myVehicleToLightTransform.globalToLocal(lightPosition.roll, lightPosition.pitch, lightPosition.heading,
		stk::Vector3(myVehicleEyePosition.x + lightPosition.x, lightPosition.y, lightPosition.z));

	stk::Transform eyeToVehicleTransform;
	eyeToVehicleTransform.localToGlobal(0.0, 0.0, 0.0, myVehicleEyePosition);

	myEyeToLightTransform = myVehicleToLightTransform * eyeToVehicleTransform;

	osg::Camera* camera = myView->getCamera();
	myPicto3D.setPixelCoords(myWidth, myHeight, myVehicleToLightTransform, myEyeToLightTransform, camera->getViewMatrix(), camera->getProjectionMatrix());
}

//=============================================================================

void SensorsViewer::updateBoundingBox(
	ObjectBoundingBox::BBoxType boxType,
	short boxID,
	const stk::Vector3 &rearBottomRight,
	const stk::Vector3 &rearTopRight,
	const stk::Vector3 &rearbottomLeft,
	const stk::Vector3 &rearTopLeft,
	const stk::Vector3 &frontBottomRight,
	const stk::Vector3 &frontTopRight,
	const stk::Vector3 &frontbottomLeft,
	const stk::Vector3 &frontTopLeft)
{
	//select the map to update
	std::map <short, ObjectBoundingBox> *boxesMap = &myMobilesBBoxes;
	if (boxType == ObjectBoundingBox::BBox_Infra)
		boxesMap = &myInfraBBoxes;

	//get or insert the box
	ObjectBoundingBox newBox;
	std::pair<std::map<short, ObjectBoundingBox>::iterator, bool> insertResult = boxesMap->insert(std::pair<short, ObjectBoundingBox>(boxID, newBox));
	std::map <short, ObjectBoundingBox>::iterator itBox = insertResult.first;
	if (insertResult.second == true)
	{
		myCompositeViewer->stopThreading();

		//the box is new, create its 3D rep...
		itBox->second.create3DBoundingBox();
		//my3DScene->addChild(itBox->second.get3DBoundingBoxDebugRep());

		//...and 2D rep
		itBox->second.create2DBoundingBox();
		my2DScene->addChild(itBox->second.get2DBoundingBoxDebugRep());

		myCompositeViewer->startThreading();
	}
	

	stk::Vector3 rearBottomRightInLight = myVehicleToLightTransform.apply(rearBottomRight);
	stk::Vector3 rearTopRightInLight = myVehicleToLightTransform.apply(rearTopRight);
	stk::Vector3 rearBottomLeftInLight = myVehicleToLightTransform.apply(rearbottomLeft);
	stk::Vector3 rearTopLeftInLight = myVehicleToLightTransform.apply(rearTopLeft);
	stk::Vector3 frontBottomRightInLight = myVehicleToLightTransform.apply(frontBottomRight);
	stk::Vector3 frontTopRightInLight = myVehicleToLightTransform.apply(frontTopRight);
	stk::Vector3 frontBottomLeftInLight = myVehicleToLightTransform.apply(frontbottomLeft);
	stk::Vector3 frontTopLeftInLight = myVehicleToLightTransform.apply(frontTopLeft);

	//update the box
	itBox->second.updatePoints(
		rearBottomRightInLight,
		rearTopRightInLight,
		rearBottomLeftInLight,
		rearTopLeftInLight,
		frontBottomRightInLight,
		frontTopRightInLight,
		frontBottomLeftInLight,
		frontTopLeftInLight);
	itBox->second.show();

	osg::Camera* camera = myView->getCamera();
	itBox->second.project(camera->getViewMatrix(), camera->getProjectionMatrix());
}

//=============================================================================

void SensorsViewer::hideBoxes()
{
	std::map <short, ObjectBoundingBox>::iterator itBox;
	for (itBox = myMobilesBBoxes.begin(); itBox != myMobilesBBoxes.end(); ++itBox)
	{
		itBox->second.hide();
	}
	for (itBox = myInfraBBoxes.begin(); itBox != myInfraBBoxes.end(); ++itBox)
	{
		itBox->second.hide();
	}
}

//=============================================================================

void SensorsViewer::displayPicto()
{
	myPicto3D.getGeode()->setNodeMask(0xffffffff);
}

//=============================================================================

void SensorsViewer::hidePicto()
{
	myPicto3D.getGeode()->setNodeMask(0x0);
}

//=============================================================================

void SensorsViewer::clear ()
{	
	my3DScene->removeChildren(0, my3DScene->getNumChildren());
	my2DScene->removeChildren(0, my2DScene->getNumChildren());
	myMobilesBBoxes.clear();
	myInfraBBoxes.clear();
}
