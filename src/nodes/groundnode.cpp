/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "quberaid.hpp"
#include "resources.hpp"
#include "nodes/groundnode.hpp"
#include "meshes/roundedcubemesh.hpp"

using namespace irr;


GroundNode::GroundNode(QubeRaid* app, const std::vector<Level::GroundBlock>& blocks) :
	BaseNode(app)
{
	setOutline(true);
	m_material = app->getResources()->getMaterial(Resources::Material::GROUND);

	for (auto& block : blocks)
	{
		addBlock(block);
	}

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	setPosition( -getBoundingBox().getCenter() );
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
