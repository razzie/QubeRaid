/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include <gg/logger.hpp>
#include "application.hpp"
#include "level/level.hpp"
#include "events/inputevents.hpp"
#include "tasks/leveltask.hpp"
#include "tasks/cameracontroller.hpp"
//#include "nodes/groundnode.hpp"
#include "nodes/terrainnode.hpp"
//#include "nodes/quboidnode.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


LevelTask::LevelTask(Application* app) :
	m_app(app)
{
	//auto level = std::make_shared<Level>(m_app);
	//m_app->setLevel(level);

	//m_ground = new GroundNode(m_app, level->getGroundBlocks());
	//resetCamera();

	//m_quboids.push_back(new QuboidNode(m_app));
	//auto pos = level->getIslands()[0].position;
	//pos.X += 2.f;
	//m_quboids[0]->setPosition({ pos.X, m_ground->getHeight(pos), pos.Y });

	m_terrain = new TerrainNode(app, 12345, { 32, 32 });
	resetCamera();
}

LevelTask::~LevelTask()
{
	//m_ground->drop();
	m_terrain->drop();
}

void LevelTask::onStart(gg::ITaskOptions& options)
{
	options.subscribe(key_event);
	options.subscribe(mouse_event);
	//options.getThread().addTask<CameraController, Application::State::GAME>(m_app);
}

void LevelTask::onEvent(gg::ITaskOptions& options, gg::EventPtr e)
{
	if (e->is(key_event))
	{
		const KeyInput* event;
		e->get(event);

		if (!event->consumed)
		{
			EKEY_CODE key = static_cast<EKEY_CODE>(event->key_code);
			switch (key)
			{
			case EKEY_CODE::KEY_SPACE:
				resetCamera();
				event->consumed = true;
				break;

			default:
				break;
			}
		}
	}

	if (e->is(mouse_event))
	{
		const MouseInput* event;
		e->get(event);

		if (!event->consumed && event->left_button_clicked)
		{
			core::plane3df plane(core::vector3df(0.f, 0.f, 0.f), core::vector3df(0.f, 1.f, 0.f));
			core::vector3df intersection;
			core::line3df ray = m_app->getSceneManager()->getSceneCollisionManager()->getRayFromScreenCoordinates({ event->x, event->y });
			if (plane.getIntersectionWithLine(ray.start, ray.end + ray.start, intersection))
			{
				//m_quboids[0]->walkTo({ intersection.X, intersection.Z });
			}
		}
	}
}

void LevelTask::onUpdate(gg::ITaskOptions& options)
{
	//auto target_pos = m_quboids[0]->getPosition();
	//target_pos.Y = 0.f;
	//m_app->getCamera()->setTarget(target_pos);
}

void LevelTask::onStateChange(gg::ITaskOptions& options, gg::IThread::State old_state, gg::IThread::State new_state)
{
}

void LevelTask::onError(gg::ITaskOptions& options, std::exception& e)
{
	gg::log << e.what() << std::endl;
}

void LevelTask::onFinish(gg::ITaskOptions& options)
{
}

void LevelTask::resetCamera()
{
	auto center = /*m_ground*/m_terrain->getBoundingBox().getCenter();
	m_app->getCamera()->setPosition(center + core::vector3df{ 0.f, 10.f, -10.f });
	m_app->getCamera()->setTarget(center);
}
