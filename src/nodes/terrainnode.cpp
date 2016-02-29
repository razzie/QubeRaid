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


TerrainNode::TerrainNode(Application* app, uint32_t seed, core::dimension2du size) :
	BaseNode(app)
{
	setOutline(true, 1.f, 0.f);
	m_material = *app->getResources()->get<video::SMaterial>("material_cell");
	//m_material.BackfaceCulling = false;
	//m_material.Wireframe = true;

	PerlinNoise<256> noise(seed);

	MarchingCubes builder(size.Width, 10, size.Height);
	builder.getGrid().foreach([&](float* value, int x, int y, int z)
	{
		float n = noise(0.125f * x, 0.125f * y, 0.125f * z) + 0.5f;

		if (x < 10) n -= 0.1f * (10 - x);
		else if (x > size.Width - 10) n -= 0.1f * (x - (size.Width - 10));
		if (z < 10) n -= 0.1f * (10 - z);
		else if (z > size.Height - 10) n -= 0.1f * (z - (size.Height - 10));

		n -= 0.1f * y;
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
