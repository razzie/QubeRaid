/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include <gg/logger.hpp>
#include "level/level.hpp"
#include "level/pathfinder.hpp"

using namespace irr;


Pathfinder::Pathfinder(const Level* level)
{
	for (auto& block : level->getGroundBlocks())
	{
		if (block.box.MinEdge.Y != 0)
			continue;

		core::dimension2di size(block.box.getExtent().X, block.box.getExtent().Z);
		for (int x = 0; x < size.Width; ++x)
		{
			for (int y = 0; y < size.Height; ++y)
			{
				core::vector2df pos((f32)(x + block.box.MinEdge.X), (f32)(y + block.box.MinEdge.Z));

				State state;
				state.place = core::rectf(pos, pos + core::vector2df{ 1.f, 1.f });
				m_states.emplace(state.place.UpperLeftCorner, state);
			}
		}
	}

	for (auto& state : m_states)
	{
		auto pos = state.first;
		auto adjacents = state.second.adjacents;
		adjacents[0] = findState(pos + core::vector2df{ 1.f, 0.f });
		adjacents[1] = findState(pos + core::vector2df{ -1.f, 0.f });
		adjacents[2] = findState(pos + core::vector2df{ 0.f, 1.f });
		adjacents[3] = findState(pos + core::vector2df{ 0.f, -1.f });
	}

	m_micropather = new micropather::MicroPather(this, m_states.size(), 4);
}

Pathfinder::~Pathfinder()
{
	delete m_micropather;
}

bool Pathfinder::getPath(const core::vector2df start, const core::vector2df end, std::vector<core::vector2df>& path_steps) const
{
	const State* start_state = findState(start);
	const State* end_state = findState(end);

	if (start_state == nullptr || end_state == nullptr)
		return false;

	std::vector<void*> path;
	float cost;
	int rc = m_micropather->Solve((void*)start_state, (void*)end_state, &path, &cost);

	if (rc != micropather::MicroPather::SOLVED)
		return false;

	for (void* state : path)
		path_steps.push_back(((State*)state)->place.getCenter());
	return true;
}

bool Pathfinder::findClosest(const irr::core::vector2df position, irr::core::vector2df& closest_position) const
{
	for (auto& it : m_states)
	{
		if (it.second.place.isPointInside(position))
		{
			closest_position = it.first;
			return true;
		}
	}

	return false;
}

float Pathfinder::LeastCostEstimate(void* stateStart, void* stateEnd)
{
	return ((State*)stateStart)->place.UpperLeftCorner.getDistanceFrom(((State*)stateEnd)->place.UpperLeftCorner);
}

void Pathfinder::AdjacentCost(void* state, std::vector<micropather::StateCost>* adjacent)
{
	auto adjacents = ((State*)state)->adjacents;
	for (int i = 0; i < 4; ++i)
	{
		if (adjacents[i] == nullptr)
			continue;

		micropather::StateCost cost;
		cost.cost = 1.f;
		cost.state = (void*)adjacents[i];
		adjacent->push_back(cost);
	}
}

void Pathfinder::PrintStateInfo(void* state)
{
	auto pos = ((State*)state)->place.UpperLeftCorner;
	gg::log << "(" << pos.X << "," << pos.Y << ")";
}

const Pathfinder::State* Pathfinder::findState(core::vector2df pos) const
{
	pos.X = std::floor(pos.X);
	pos.Y = std::floor(pos.Y);
	auto it = m_states.find(pos);
	if (it != m_states.end())
	{
		return &(it->second);
	}
	else
	{
		return nullptr;
	}
}
