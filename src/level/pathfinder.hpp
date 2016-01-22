/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <map>
#include <micropather/micropather.h>
#include <irrlicht.h>

class Level;

class Pathfinder : public micropather::Graph
{
public:
	Pathfinder(const Level*);
	~Pathfinder();
	bool getPath(const irr::core::vector2df start, const irr::core::vector2df end, std::vector<irr::core::vector2df>& path_steps) const;
	bool findClosest(const irr::core::vector2df position, irr::core::vector2df& closest_position) const;

	// inherited from micropather::Graph
	virtual float LeastCostEstimate(void* stateStart, void* stateEnd);
	virtual void AdjacentCost(void* state, std::vector<micropather::StateCost>* adjacent);
	virtual void  PrintStateInfo(void* state);

private:
	struct State
	{
		irr::core::rectf place;
		micropather::StateCost adjacents[8];
	};

	std::map<irr::core::vector2df, State> m_states;
	mutable micropather::MicroPather* m_micropather;

	const State* findState(irr::core::vector2df pos) const;
};
