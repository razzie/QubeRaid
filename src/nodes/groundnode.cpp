/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <cmath>
#include "quberaid.hpp"
#include "nodes/groundnode.hpp"
#include "meshes/cubemesh.hpp"
#include "meshes/roundedcubemesh.hpp"

using namespace irr;


GroundNode::GroundNode(QubeRaid* app, const std::vector<Level::GroundBlock>& blocks) :
	BaseNode(app)
{
	setOutline(true);
	m_material = *app->getResources()->get<video::SMaterial>("material_ground");

	for (auto& block : blocks)
	{
		addBlock(block);
	}

	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
	{
		auto& pos = m_vertices[i].Pos;
		pos.Y += getHeight({ pos.X, pos.Z });
	}

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	scene::ISceneManager* smgr = getSceneManager();
	for (auto& island : m_app->getLevel()->getIslands())
	{
		auto* billboard = smgr->addBillboardSceneNode(this, { 2.f, 2.f }, { island.position.X, getHeight(island.position) + 1.0f, island.position.Y });
		billboard->setMaterialTexture(0, m_app->getDriver()->getTexture("../assets/home.png"));
		billboard->setMaterialType(video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
		billboard->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	}
}

GroundNode::~GroundNode()
{
}

f32 GroundNode::getHeight(core::vector2df pos)
{
	return (std::sin(pos.X * 0.15f) + std::cos(pos.Y * 0.15f));
}

void GroundNode::addBlock(const Level::GroundBlock& block)
{
	core::vector3di pos = block.box.MinEdge;
	core::vector3di size = block.box.MaxEdge - block.box.MinEdge;

	core::vector3df fpos((f32)pos.X, (f32)pos.Y, (f32)pos.Z);
	core::vector3df fsize((f32)size.X, (f32)size.Y, (f32)size.Z);
	fsize -= core::vector3df(0.1f);

	RoundedCubeMesh().append(&m_meshbuffer, fpos, fsize, block.color);
}
