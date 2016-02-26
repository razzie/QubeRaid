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
#include "utils/marchingcubes.hpp"

using namespace irr;


TerrainNode::TerrainNode(Application* app, uint32_t seed, uint32_t size) :
	BaseNode(app)
{
	setOutline(true, 1.f, 0.f);
	m_material = *app->getResources()->get<video::SMaterial>("material_cell");
	//m_material.BackfaceCulling = false;
	//m_material.Wireframe = true;

	PerlinNoise<256> noise(seed);
	core::vector2df center(0.5f * size, 0.5f * size);
	f32 maxdist = 0.5f * size;

	MarchingCubes builder(size, 10, size);
	builder.getGrid().foreach([&](float* value, int x, int y, int z)
	{
		core::vector2df p((f32)x, (f32)z);
		float n = noise(0.125f * x, 0.25f * y, 0.125f * z);
		n += (1.f - (p.getDistanceFrom(center) / maxdist));
		n -= 0.2f * y;
		if (y == 0) n = 0.f;
		else if (y > 1) n -= 0.5f;
		//*value = n > 0.f ? 1.f : -1.f;
		*value = n / 4.f;
	});
	builder.build(&m_meshbuffer, true);

	//SceneManager->getMeshManipulator()->recalculateNormals(&m_meshbuffer);

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();
}

TerrainNode::~TerrainNode()
{
}
