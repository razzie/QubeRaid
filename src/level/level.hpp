/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <vector>
#include <irrlicht.h>

class Application;
class Pathfinder;

class Level
{
public:
	struct Island
	{
		irr::core::vector2df position;
		float radius;

		bool isInRange(irr::core::vector2df p) const
		{
			return (p.getDistanceFrom(position) < (radius));
		}
	};

	struct Route
	{
		const Island* A;
		const Island* B;
		float thickness;

		bool isInRange(irr::core::vector2df p) const
		{
			return (irr::core::line2df(A->position, B->position).getClosestPoint(p).getDistanceFrom(p) < (thickness));
		}
	};

	struct GroundBlock
	{
		irr::core::aabbox3di box;
		irr::video::SColor color = 0xffffffff;
	};

	struct GroundPlatform
	{
		irr::core::recti platform;
	};

	Level(Application*);
	~Level();
	const Pathfinder* getPathfinder() const;
	const std::vector<Island>& getIslands() const;
	const std::vector<Route>& getRoutes() const;
	const std::vector<GroundBlock>& getGroundBlocks() const;
	const std::vector<GroundPlatform>& getGroundPlatforms() const;

private:
	Application* m_app;
	Pathfinder* m_pathfinder;
	irr::core::dimension2du m_size;
	std::vector<Island> m_islands;
	std::vector<Route> m_routes;
	std::vector<GroundBlock> m_ground_blocks;
	std::vector<GroundPlatform> m_ground_platforms;
};
