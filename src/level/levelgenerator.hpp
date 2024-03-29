/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <cstdint>
#include <vector>
#include <irrlicht.h>
#include "level/level.hpp"

class LevelGenerator
{
public:
	enum Pattern
	{
		STAR,
		RING,
		RANDOM_GRAPH
	};

	LevelGenerator(uint32_t seed);
	~LevelGenerator();
	void generate(Pattern pattern, unsigned islands, unsigned tiny_islands, std::vector<Level::Island>& out_islands, std::vector<Level::Route>& out_routes) const;
	void generate(const std::vector<Level::Island>& in_islands, const std::vector<Level::Route>& in_routes, std::vector<Level::GroundBlock>& out_ground_blocks) const;
	void generate(const std::vector<Level::GroundBlock>& in_blocks, std::vector<Level::GroundPlatform>& out_platforms) const;
	void optimize(std::vector<Level::Island>& islands) const;

private:
	uint32_t m_seed;
};
