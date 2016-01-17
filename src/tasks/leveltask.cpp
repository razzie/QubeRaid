/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include <gg/logger.hpp>
#include "quberaid.hpp"
#include "level/level.hpp"
#include "events/inputevents.hpp"
#include "tasks/leveltask.hpp"
#include "tasks/cameracontroller.hpp"
#include "nodes/groundnode.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


LevelTask::LevelTask(QubeRaid* app) :
	m_app(app)
{
	auto level = std::make_shared<Level>(m_app);
	m_app->setLevel(level);

	m_ground = new GroundNode(m_app, level->getGroundBlocks());
}

LevelTask::~LevelTask()
{
	m_ground->drop();
}

void LevelTask::onStart(gg::ITaskOptions& options)
{
	//options.subscribe(key_event);
	//options.getThread().addTask<CameraController, QubeRaid::State::GAME>(m_app);
}

void LevelTask::onEvent(gg::ITaskOptions& options, gg::EventPtr e)
{
	//if (e->is(key_event))
	//{
	//	const KeyInput* event;
	//	e->get(event);

	//	if (!event->consumed)
	//	{
	//		event->consumed = true;

	//		EKEY_CODE key = static_cast<EKEY_CODE>(event->key_code);
	//		switch (key)
	//		{
	//		default:
	//			break;
	//		}
	//	}
	//}
}

void LevelTask::onUpdate(gg::ITaskOptions& options)
{
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
