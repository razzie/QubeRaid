/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "level/level.hpp"
#include "level/levelgenerator.hpp"
#include "level/pathfinder.hpp"
#include "application.hpp"

using namespace irr;


Level::Level(Application* app) :
	m_app(app)
{
	LevelGenerator gen(12345);
	gen.generate(LevelGenerator::Pattern::STAR, 6, 0, m_islands, m_routes);
	gen.optimize(m_islands);
	gen.generate(m_islands, m_routes, m_ground_blocks);
	gen.generate(m_ground_blocks, m_ground_platforms);

	m_pathfinder = new Pathfinder(this);
}

Level::~Level()
{
	delete m_pathfinder;
}

const Pathfinder* Level::getPathfinder() const
{
	return m_pathfinder;
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

const std::vector<Level::GroundPlatform>& Level::getGroundPlatforms() const
{
	return m_ground_platforms;
}
