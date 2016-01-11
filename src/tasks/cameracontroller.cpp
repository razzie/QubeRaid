/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <irrlicht.h>
#include "quberaid.hpp"
#include "events.hpp"
#include "tasks/cameracontroller.hpp"


static void rotateAroundCentre(irr::core::vector3df& point, irr::core::vector3df center, irr::core::vector3df rotation)
{
	point -= center;
	irr::core::matrix4 m;
	m.setRotationDegrees(rotation);
	m.rotateVect(point);
	point += center;
}

static void rotateVectorAroundAxis(irr::core::vector3df& vector, const irr::core::vector3df& axis, irr::f32 radians)
{
	irr::core::quaternion q;
	irr::core::matrix4 m;
	q.fromAngleAxis(radians, axis);
	q.getMatrix(m, irr::core::vector3df(0, 0, 0));
	m.rotateVect(vector);
}


CameraController::CameraController(QubeRaid* app) :
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

	irr::core::vector2di curr_pos(event->x, event->y);
	irr::core::vector2di delta(event->x_delta, event->y_delta);
	irr::scene::ICameraSceneNode* cam = m_app->getCamera();
	uint32_t elapsedMs = options.getElapsedMs();
	float speed = static_cast<float>(elapsedMs) / 20.f;

	if (event->right_button)
	{
		irr::core::vector3df pos = cam->getPosition();
		irr::core::vector3df target = cam->getTarget();
		irr::core::vector3df right = irr::core::vector3df(0.f, 1.f, 0.f).crossProduct(target - pos);
		right.normalize();

		pos -= target;
		rotateVectorAroundAxis(pos, right, speed * delta.Y * irr::core::DEGTORAD);
		pos += target;
		pos.rotateXZBy(speed * -delta.X, target);

		cam->setPosition(pos);
	}

	if (event->wheel > 0)
	{
		irr::core::vector3df cam_pos = cam->getPosition();
		cam_pos *= 0.9f;
		cam->setPosition(cam_pos);
	}
	else if (event->wheel < 0)
	{
		irr::core::vector3df cam_pos = cam->getPosition();
		cam_pos *= 1.1f;
		cam->setPosition(cam_pos);
	}
}

void CameraController::onUpdate(gg::ITaskOptions& options)
{
}
