/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "quberaid.hpp"
#include "nodes/groundnode.hpp"
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

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	setPosition({ 0.f, -1.f, 0.f });

	scene::ISceneManager* smgr = getSceneManager();
	for (auto& island : m_app->getLevel()->getIslands())
	{
		auto* billboard = smgr->addBillboardSceneNode(this, { 2.f, 2.f }, { island.position.X, 2.5f, island.position.Y });
		billboard->setMaterialTexture(0, m_app->getDriver()->getTexture("../assets/home.png"));
		billboard->setMaterialType(video::E_MATERIAL_TYPE::EMT_TRANSPARENT_ALPHA_CHANNEL_REF);
		billboard->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_LIGHTING, false);
	}
}

GroundNode::~GroundNode()
{
}

void GroundNode::addBlock(const Level::GroundBlock& block)
{
	core::vector3di pos = block.box.MinEdge;
	core::vector3di size = block.box.MaxEdge - block.box.MinEdge;

	core::vector3df fpos((f32)pos.X, (f32)pos.Y, (f32)pos.Z);
	core::vector3df fsize((f32)size.X, (f32)size.Y, (f32)size.Z);

	RoundedCubeMesh().append(&m_meshbuffer, fpos, fsize, block.color);
}
