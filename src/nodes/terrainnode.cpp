/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
#include <randomlib/Random.hpp>
#include "application.hpp"
#include "nodes/terrainnode.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


TerrainNode::TerrainNode(Application* app, uint32_t seed, uint32_t size) :
	BaseNode(app)
{
	//setOutline(true);
	m_material = *app->getResources()->get<video::SMaterial>("material_flat");
	m_material.BackfaceCulling = false;

	struct GridPoint
	{
		uint16_t index;
		uint16_t solid : 1;
	};

	Grid3D<GridPoint> grid(size, 3, size);
	PerlinNoise<256> noise(seed);
	core::vector2df center(0.5f * size, 0.5f * size);
	f32 maxdist = 0.5f * size;

	grid.foreach([&](GridPoint* data, size_t x, size_t y, size_t z)
	{
		core::vector2df p((f32)x, (f32)z);
		float n = noise(0.125f * x, 0.25f * y, 0.125f * z) + (1.f - (p.getDistanceFrom(center) / maxdist)) - (0.5f * y);

		//if (x == 12 && y == 0) n = 0.f;

		unsigned color = 128 + (n * 128);
		if (color > 255) color = 255;

		video::S3DVertex v(core::vector3df((f32)x, (f32)y * 2.f + n, (f32)z), core::vector3df(0.f, 1.f, 0.f), video::SColor(255, y == 0 ? 64 : color, color, y == 0 ? 64 : color), core::vector2df(0.f, 0.f));
		data->solid = n > 0.f;
		data->index = m_vertices.size();
		m_vertices.push_back(v);
	});

	std::vector<std::pair<GridPoint*,bool>> points;
	grid.foreach([&](GridPoint* data, size_t x, size_t y, size_t z)
	{
		//  (0)---(1)
		//   |     |
		//  (3)---(2)

		GridPoint* p;

		// 0
		if (nullptr != (p = grid(x, y + 1, z)) && p->solid)
			points.push_back({ p, true });
		else if (data->solid)
			points.push_back({ data, false });

		// 1
		if (nullptr != (p = grid(x + 1, y + 1, z)) && p->solid)
			points.push_back({ p, true });
		else if (nullptr != (p = grid(x + 1, y, z)) && p->solid)
			points.push_back({ p, false });

		// 2
		if (nullptr != (p = grid(x + 1, y + 1, z + 1)) && p->solid)
			points.push_back({ p, true });
		else if (nullptr != (p = grid(x + 1, y, z + 1)) && p->solid)
			points.push_back({ p, false });

		// 3
		if (nullptr != (p = grid(x, y + 1, z + 1)) && p->solid)
			points.push_back({ p, true });
		else if (nullptr != (p = grid(x, y, z + 1)) && p->solid)
			points.push_back({ p, false });

		if (points.size() >= 3)
		{
			auto elevations = std::count_if(points.begin(), points.end(), [](auto& it) { return it.second; });

			//if (elevations == points.size())
			//	return;

			//if (elevations >= 3)
			//{
			//	int e = 0;
			//	for (auto it = points.begin(), end = points.end(); it != end; ++it)
			//	{
			//		if (it->second)
			//			++elevations;

			//		if (e == 2)
			//		{
			//			points.erase(it);
			//			break;
			//		}
			//	}
			//}

			for (size_t i = 0, len = points.size(); i < len; ++i)
			{
				if (points[i].second && (i % 2 == 0))
				{
					std::rotate(points.begin(), points.begin() + 1, points.end());
					break;
				}
			}

			m_indices.push_back(points[0].first->index);
			m_indices.push_back(points[2].first->index);
			m_indices.push_back(points[1].first->index);

			if (points.size() == 4)
			{
				m_indices.push_back(points[0].first->index);
				m_indices.push_back(points[3].first->index);
				m_indices.push_back(points[2].first->index);
			}
		}

		points.clear();
	});

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	SceneManager->getMeshManipulator()->recalculateNormals(&m_meshbuffer);
}

TerrainNode::~TerrainNode()
{
}
