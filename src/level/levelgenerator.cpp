/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include <random>
#include "levelgenerator.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


LevelGenerator::LevelGenerator(unsigned seed) :
	m_seed(seed)
{
}

LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::generate(Pattern pattern, unsigned islands, unsigned tiny_islands, std::vector<Level::Island>& out_islands, std::vector<Level::Route>& out_routes) const
{
	if (pattern == Pattern::STAR)
	{
		unsigned islands_sum = islands + tiny_islands;

		if (islands_sum < 1)
			return;

		float level_radius = 20.f + (islands * 10.f) + (tiny_islands * 5.f);
		float island_angle = 360.f / (islands_sum - 1);
		core::vector2df center(level_radius * 0.5f, level_radius * 0.5f);

		Level::Island center_island;
		center_island.position = center;
		if (islands > 0)
		{
			center_island.radius = 5.f;
			--islands;
			--islands_sum;
		}
		else
		{
			center_island.radius = 2.5f;
			--tiny_islands;
			--islands_sum;
		}
		out_islands.push_back(center_island);

		for (unsigned i = 0; i < islands_sum; ++i)
		{
			core::vector2df pos(std::sin(core::degToRad(island_angle * i)), std::cos(core::degToRad(island_angle * i)));
			pos *= (level_radius * 0.25f);
			pos += center;

			Level::Island island;
			island.position = pos;

			if (islands > tiny_islands)
			{
				--islands;
				island.radius = 5.f;
			}
			else
			{
				--tiny_islands;
				island.radius = 2.5f;
			}

			out_islands.push_back(island);
		}

		for (const auto& island : out_islands)
		{
			if (&island == &out_islands[0])
				continue;

			Level::Route route;
			route.A = &out_islands[0];
			route.B = &island;
			route.thickness = 2.f;
			out_routes.push_back(route);
		}
	}
	else if (pattern == Pattern::RING)
	{
		unsigned islands_sum = islands + tiny_islands;

		if (islands_sum < 1)
			return;

		float level_radius = 20.f + (islands * 10.f) + (tiny_islands * 5.f);
		float island_angle = 360.f / islands_sum;
		core::vector2df center(level_radius * 0.5f, level_radius * 0.5f);

		for (unsigned i = 0; i < islands_sum; ++i)
		{
			core::vector2df pos(std::sin(core::degToRad(island_angle * i)), std::cos(core::degToRad(island_angle * i)));
			pos *= (level_radius * 0.25f);
			pos += center;

			Level::Island island;
			island.position = pos;

			if (islands > tiny_islands)
			{
				--islands;
				island.radius = 5.f;
			}
			else
			{
				--tiny_islands;
				island.radius = 2.5f;
			}

			out_islands.push_back(island);
		}

		for (unsigned i = 0, cnt = out_islands.size(); i < cnt; ++i)
		{
			Level::Route route;
			route.A = &out_islands[i];
			route.B = &out_islands[(i + 1) % cnt];
			route.thickness = 2.f;
			out_routes.push_back(route);
		}
	}
	else if (pattern == Pattern::RANDOM_GRAPH)
	{
		// TODO
	}
}

void LevelGenerator::generate(const std::vector<Level::Island>& in_islands, const std::vector<Level::Route>& in_routes, std::vector<Level::GroundBlock>& out_ground_blocks) const
{
	struct GridData
	{
		unsigned char solid : 1;
		volatile unsigned char used : 1;
	};

	const int level_height = 3;
	core::vector3di level_size(0, level_height, 0);
	for (auto& island : in_islands)
	{
		if (level_size.X < (s32)(island.position.X + island.radius) + 1)
			level_size.X = (s32)(island.position.X + island.radius) + 1;
		if (level_size.Z < (s32)(island.position.Y + island.radius) + 1)
			level_size.Z = (s32)(island.position.Y + island.radius) + 1;
	}

	Grid3D<GridData> grid(level_size.X, level_size.Y, level_size.Z);
	PerlinNoise<256> noise(m_seed);

	auto is_solid = [&](core::vector2df p)
	{
		for (auto& island : in_islands)
		{
			if (island.isInRange(p))
				return true;
		}

		for (auto& route : in_routes)
		{
			if (route.isInRange(p))
				return true;
		}

		return false;
	};

	grid.foreach([&](GridData* data, size_t x, size_t y, size_t z)
	{
		core::vector2df p((f32)x, (f32)z);
		float n = noise(0.125f * x, 0.125f * y, 0.125f * z) + (is_solid(p) ? 0.5f : -0.25f);
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

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<u32> dis(160, 255);

	auto add_block = [&](core::vector3di pos, core::vector3di size)
	{
		Level::GroundBlock block;
		pos.Y -= level_height;
		block.box.MinEdge = pos;
		block.box.MaxEdge = pos + size;
		//block.color = 0xffffffff;
		u32 color = dis(gen) + ((pos.Y + size.Y) * 64);
		block.color = video::SColor(255, color, color, color);
		out_ground_blocks.push_back(block);
	};

	grid.foreach([&](GridData* data, size_t x, size_t y, size_t z)
	{
		if (data->used)
			return;

		core::vector3di pos((int)x, (int)y, (int)z);

		if (dis(gen) % 2 && find_block(pos, { 3, 1, 2 }))
			add_block(pos, { 3, 1, 2 });
		else if (dis(gen) % 2 && find_block(pos, { 2, 1, 3 }))
			add_block(pos, { 2, 1, 3 });
		else if (find_block(pos, { 2, 1, 2 }))
			add_block(pos, { 2, 1, 2 });
		else if (data->solid)
			add_block(pos, { 1, 1, 1 });
	});
}

void LevelGenerator::optimize(std::vector<Level::Island>& islands) const
{
	if (islands.empty())
		return;

	core::vector2df min_edge = islands[0].position;
	for (auto& island : islands)
	{
		if (min_edge.X > (island.position.X - island.radius))
			min_edge.X = (island.position.X - island.radius);
		if (min_edge.Y > (island.position.Y - island.radius))
			min_edge.Y = (island.position.Y - island.radius);
	}

	for (auto& island : islands)
	{
		island.position -= min_edge;
	}
}
