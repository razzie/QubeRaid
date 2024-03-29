/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "application.hpp"
#include "events/inputevents.hpp"
#include "tasks/cameracontroller.hpp"

using namespace irr;


static void rotateAroundCentre(core::vector3df& point, core::vector3df center, core::vector3df rotation)
{
	point -= center;
	core::matrix4 m;
	m.setRotationDegrees(rotation);
	m.rotateVect(point);
	point += center;
}

static void rotateVectorAroundAxis(core::vector3df& vector, const core::vector3df& axis, f32 radians)
{
	core::quaternion q;
	core::matrix4 m;
	q.fromAngleAxis(radians, axis);
	q.getMatrix(m, core::vector3df(0, 0, 0));
	m.rotateVect(vector);
}


CameraController::CameraController(Application* app) :
	m_app(app)
{
}

CameraController::~CameraController()
{
}

void CameraController::onStart(gg::ITaskOptions& options)
{
	options.subscribe(mouse_event);
}

void CameraController::onEvent(gg::ITaskOptions& options, gg::EventPtr e)
{
	if (!e->is(mouse_event))
		return;

	const MouseInput* event;
	e->get(event);

	if (event->consumed)
		return;
	else
		event->consumed = true;

	core::vector2di curr_pos(event->x, event->y);
	core::vector2di delta(event->x_delta, event->y_delta);
	scene::ICameraSceneNode* cam = m_app->getCamera();
	uint32_t elapsedMs = options.getElapsedMs();
	float speed = static_cast<float>(elapsedMs) / 40.f;

	if (event->right_button_down)
	{
		core::vector3df pos = cam->getPosition();
		core::vector3df target = cam->getTarget();
		core::vector3df right = core::vector3df(0.f, 1.f, 0.f).crossProduct(target - pos);
		right.normalize();

		pos -= target;
		rotateVectorAroundAxis(pos, right, speed * delta.Y * core::DEGTORAD);
		pos += target;
		pos.rotateXZBy(speed * -delta.X, target);

		cam->setPosition(pos);
	}

	if (event->wheel > 0)
	{
		core::vector3df target = cam->getTarget();
		core::vector3df cam_pos = cam->getPosition();
		cam_pos -= target;
		cam_pos *= 0.9f;
		cam_pos += target;
		cam->setPosition(cam_pos);
	}
	else if (event->wheel < 0)
	{
		core::vector3df target = cam->getTarget();
		core::vector3df cam_pos = cam->getPosition();
		cam_pos -= target;
		cam_pos *= 1.1f;
		cam_pos += target;
		cam->setPosition(cam_pos);
	}
}

void CameraController::onUpdate(gg::ITaskOptions& options)
{
}
