#pragma once

#include "ObjectBoundingBox.h"
#include "Picto3D.h"

#include "stk/Transform.h"

#include <vector>
#include <map>
#include <osg/Node>

namespace stk
{
	class Vector3;
}

namespace osg
{
	class GraphicsContext;
	class Camera;
}

namespace osgViewer
{
	class View;
	class CompositeViewer;
}


class SensorsViewer
{
public:

	SensorsViewer(const std::string& procName, int viewerWidth, int viewerHeight);

	virtual ~SensorsViewer();

	/**
	 * Initializes the OSG sensor scene viewer.
	 */
	void load();

	/**
	 * Unloads the sensor manager.
	 */
	void unload();

	/**
	 * Renders a frame.
	 */
	void update();

	/**
	 * Sets the headlight vehicle eye position.
	 * @param[in] eyePosition the vehicle 0 eye position.
	 */
	void setVehicleEyePosition(const stk::Vector3& eyePosition);

	/**
	 * Updates the light source position.
	 * @param[in] lightPosition the new light source position.
	 */
	void updateLightSourcePosition(const stk::Mark& lightPosition);

	/**
	 * Adds the given sensor to the OSG Scene.
	 */
	void updateBoundingBox(
		ObjectBoundingBox::BBoxType boxType,
		short boxID,
		const stk::Vector3 &rearBottomRight,
		const stk::Vector3 &rearTopRight,
		const stk::Vector3 &rearbottomLeft,
		const stk::Vector3 &rearTopLeft,
		const stk::Vector3 &frontBottomRight,
		const stk::Vector3 &frontTopRight,
		const stk::Vector3 &frontbottomLeft,
		const stk::Vector3 &frontTopLeft);

	void hideBoxes();

	void displayPicto();

	void hidePicto();

	/**
	 * Clears the sensors.
	 */
	void clear();

private:

	/** The SCANeR process name */
	const std::string myProcName;

	/**
	 * Keep a ref on Graphical Context, to avoid its deletion when removing views from composite viewer.
	 * So we can explicitly call osg::GraphicsContext::close(true) for pbuffer mode.
	 */
	osg::ref_ptr<osg::GraphicsContext> myGC;

	/** The OSG viewer */
	osgViewer::CompositeViewer* myCompositeViewer;

	/** The OSG view */
	osgViewer::View* myView;

	/** The OSG view camera */
	osg::Camera* myCamera;

	/** The OSG viewer width */
	int myWidth;

	/** The OSG viewer height */
	int myHeight;

	/** The headlight vehicle eye position */
	stk::Vector3 myVehicleEyePosition;

	/** The eye to light transform. */
	stk::Transform myEyeToLightTransform;

	/** The vehicle to light transform. */
	stk::Transform myVehicleToLightTransform;

	/** The view scene graph root. */
	osg::Group* myRoot;

	/** The data scene graph root */
	osg::Group* my3DScene;

	/** The scene root of targets bounding boxes 2D representation. */
	osg::Group* my2DScene;

	/** The picto displayed when a crossroad is detected by a SCANeR sensor. */
	Picto3D myPicto3D;

	/** The world to openGL matrix transform */
	stk::Transform myOpenGLToSensorTransform;

	/** The map of bounding boxes */
	std::map <short, ObjectBoundingBox> myMobilesBBoxes;

	/** The map of bounding boxes */
	std::map <short, ObjectBoundingBox> myInfraBBoxes;
};
