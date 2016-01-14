/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <random>
#include "quberaid.hpp"
#include "nodes/groundnode.hpp"
#include "utils/materialfactory.hpp"
#include "utils/meshfactory.hpp"
#include "utils/perlin.hpp"
#include "utils/grid.hpp"

using namespace irr;


GroundNode::GroundNode(QubeRaid* app) :
	scene::ISceneNode(app->getSceneManager()->getRootSceneNode(), app->getSceneManager()),
	m_app(app),
	m_vertices(video::EVT_STANDARD),
	m_indices(video::EIT_16BIT),
	m_meshbuffer(video::EVT_STANDARD, video::EIT_16BIT)
{
	m_material = m_app->getMaterialFactory()->getGroundMaterial();
	m_meshbuffer.setVertexBuffer(&m_vertices);
	m_meshbuffer.setIndexBuffer(&m_indices);

	struct GridData
	{
		unsigned char solid : 1;
		volatile unsigned char used : 1;
	};

	core::vector3di size(10, 2, 10);
	Grid3D<GridData> grid(size.X, size.Y, size.Z);
	PerlinNoise<256> noise(4444);

	grid.foreach([&noise](GridData* data, size_t x, size_t y, size_t z)
	{
		float n = noise(0.25f * x, 0.25f * y, 0.25f * z);
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

	grid.foreach([&](GridData* data, size_t x, size_t y, size_t z)
	{
		if (data->used)
			return;

		core::vector3di pos((int)x, (int)y, (int)z);

		if (find_block(pos, { 3, 2, 3 }))
			addBlock(pos, { 3, 2, 3 });
		else if (find_block(pos, { 2, 1, 2 }))
			addBlock(pos, { 2, 1, 2 });
		else if (data->solid)
			addBlock(pos);
	});

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	setPosition({ -5.f, -1.f, -5.f });
}

GroundNode::~GroundNode()
{
}

void GroundNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void GroundNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

	driver->setMaterial(m_app->getMaterialFactory()->getOutlineMaterial());
	driver->drawMeshBuffer(&m_meshbuffer);

	driver->setMaterial(m_material);
	driver->drawMeshBuffer(&m_meshbuffer);
}

const core::aabbox3d<f32>& GroundNode::getBoundingBox() const
{
	return m_meshbuffer.getBoundingBox();
}

u32 GroundNode::getMaterialCount() const
{
	return 1;
}

video::SMaterial& GroundNode::getMaterial(u32 i)
{
	return m_material;
}

void GroundNode::addBlock(core::vector3di pos, core::vector3di size)
{
	core::vector3df fpos((f32)pos.X, (f32)pos.Y, (f32)pos.Z);
	core::vector3df fsize((f32)size.X, (f32)size.Y, (f32)size.Z);

	m_app->getMeshFactory()->append(MeshFactory::BuiltInMesh::ROUNDED_CUBE, &m_meshbuffer, fpos, fsize);
}
