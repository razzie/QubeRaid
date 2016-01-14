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
#include "events.hpp"
#include "tasks/leveltask.hpp"
#include "tasks/cameracontroller.hpp"
#include "nodes/groundnode.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


LevelTask::LevelTask(QubeRaid* app) :
	m_app(app)
{
	m_level_radius = 20;
	m_base_count = 5;

	generateBasePositions();
	generateGroundBlocks(4444);

	m_ground = new GroundNode(m_app, m_ground_blocks);
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

void LevelTask::generateBasePositions()
{
	float base_angle = 360.f / m_base_count;
	core::vector3df center((f32)m_level_radius, 0.f, (f32)m_level_radius);

	m_base_positions.push_back(center);

	for (unsigned i = 0; i < m_base_count; ++i)
	{
		core::vector3df base(std::sin(core::degToRad(base_angle * i)), 0.f, std::cos(core::degToRad(base_angle * i)));
		base *= (0.5f * m_level_radius);
		m_base_positions.push_back(center + base);
	}
}

void LevelTask::generateGroundBlocks(unsigned seed)
{
	struct GridData
	{
		unsigned char solid : 1;
		volatile unsigned char used : 1;
	};

	core::vector3di size(m_level_radius * 2, 2, m_level_radius * 2);
	Grid3D<GridData> grid(size.X, size.Y, size.Z);
	PerlinNoise<256> noise(seed);

	grid.foreach([&](GridData* data, size_t x, size_t y, size_t z)
	{
		float distance_factor = -(getClosestBaseDistance({ (f32)x, (f32)y, (f32)z }) - ((f32)m_level_radius * 0.25f));
		float n = noise(0.25f * x, 0.25f * y, 0.25f * z) + distance_factor;
		data->solid = n > 0.f;
		data->used = false;
	});

	auto find_block = [&](core::vector3di pos, core::vector3di size) -> bool
	{
		for (int x = pos.X; x < pos.X + size.X; ++x)
		{
			for (int y = pos.Y; y < pos.Y + size.Y; ++y)
			{
				for (int z = pos.Z; z < pos.Z + size.Z; ++z)
				{
					GridData* data = grid(x, y, z);
					if (data == nullptr || !data->solid || data->used)
						return false;
				}
			}
		}

		for (int x = pos.X; x < pos.X + size.X; ++x)
		{
			for (int y = pos.Y; y < pos.Y + size.Y; ++y)
			{
				for (int z = pos.Z; z < pos.Z + size.Z; ++z)
				{
					grid(x, y, z)->used = true;
				}
			}
		}

		return true;
	};

	grid.foreach([&](GridData* data, size_t x, size_t y, size_t z)
	{
		if (data->used)
			return;

		core::vector3di pos((int)x, (int)y, (int)z);

		if (find_block(pos, { 3, 2, 3 }))
			m_ground_blocks.push_back({ pos, { 3, 2, 3 } });
		else if (find_block(pos, { 2, 1, 2 }))
			m_ground_blocks.push_back({ pos, { 2, 1, 2 } });
		else if (data->solid)
			m_ground_blocks.push_back({ pos, { 1, 1, 1 } });
	});
}

float LevelTask::getClosestBaseDistance(irr::core::vector3df pos) const
{
	float min_distance = (float)m_level_radius;

	for (auto& base : m_base_positions)
	{
		float dist = pos.getDistanceFrom(base);
		if (dist < min_distance)
			min_distance = dist;
	}

	return min_distance;
}
