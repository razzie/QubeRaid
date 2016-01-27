/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include <random>
#include <gg/logger.hpp>
#include "level/level.hpp"
#include "level/pathfinder.hpp"

using namespace irr;


Pathfinder::Pathfinder(const Level* level)
{
	for (auto& block : level->getGroundBlocks())
	{
		if (block.box.MaxEdge.Y != 0)
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

	const float straight_cost = 1.f;
	const float diagonal_cost = 1.41421356237f;
	for (auto& state : m_states)
	{
		auto pos = state.first;
		auto adjacents = state.second.adjacents;
		adjacents[0] = { (void*)findState(pos + core::vector2df{ -1.f, -1.f }), diagonal_cost };
		adjacents[1] = { (void*)findState(pos + core::vector2df{  0.f, -1.f }), straight_cost };
		adjacents[2] = { (void*)findState(pos + core::vector2df{  1.f, -1.f }), diagonal_cost };
		adjacents[3] = { (void*)findState(pos + core::vector2df{  1.f,  0.f }), straight_cost };
		adjacents[4] = { (void*)findState(pos + core::vector2df{  1.f,  1.f }), diagonal_cost };
		adjacents[5] = { (void*)findState(pos + core::vector2df{  0.f,  1.f }), straight_cost };
		adjacents[6] = { (void*)findState(pos + core::vector2df{ -1.f,  1.f }), diagonal_cost };
		adjacents[7] = { (void*)findState(pos + core::vector2df{ -1.f,  0.f }), straight_cost };
	}

	m_micropather = new micropather::MicroPather(this, m_states.size(), 8);
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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<f32> dis(-0.25f, 0.25f);

	for (void* state : path)
	{
		core::vector2df pos = ((State*)state)->place.getCenter();
		pos.X += dis(gen);
		pos.Y += dis(gen);
		path_steps.push_back(pos);
	}
	return true;
}

bool Pathfinder::findClosest(const irr::core::vector2df position, irr::core::vector2df& closest_position) const
{
	for (auto& it : m_states)
	{
		if (it.second.place.isPointInside(position))
		{
			closest_position = it.second.place.getCenter();
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
	for (int i = 0; i < 8; ++i)
	{
		if (adjacents[i].state == nullptr)
			continue;

		adjacent->push_back(adjacents[i]);
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
