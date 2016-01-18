/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "level/level.hpp"
#include "level/levelgenerator.hpp"
#include "quberaid.hpp"

using namespace irr;


Level::Level(QubeRaid* app) :
	m_app(app)
{
	LevelGenerator gen(12345);
	gen.generate(LevelGenerator::Pattern::STAR, 6, 0, m_islands, m_routes);
	gen.optimize(m_islands);
	gen.generate(m_islands, m_routes, m_ground_blocks);
}

Level::~Level()
{
}

const std::vector<Level::Island>& Level::getIslands() const
{
	return m_islands;
}

const std::vector<Level::Route>& Level::getRoutes() const
{
	return m_routes;
}

const std::vector<Level::GroundBlock>& Level::getGroundBlocks() const
{
	return m_ground_blocks;
}
