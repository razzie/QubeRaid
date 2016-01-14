/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "quberaid.hpp"
#include "nodes/groundnode.hpp"
#include "utils/materialfactory.hpp"
#include "utils/meshfactory.hpp"

using namespace irr;


GroundNode::GroundNode(QubeRaid* app, const std::vector<std::pair<core::vector3di, core::vector3di>>& blocks) :
	NodeBase(app)
{
	setOutline(true);
	m_material = m_app->getMaterialFactory()->getGroundMaterial();

	for (auto& block : blocks)
	{
		addBlock(block.first, block.second);
	}

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();

	setPosition( -getBoundingBox().getCenter() );
}

GroundNode::~GroundNode()
{
}

void GroundNode::addBlock(core::vector3di pos, core::vector3di size)
{
	core::vector3df fpos((f32)pos.X, (f32)pos.Y, (f32)pos.Z);
	core::vector3df fsize((f32)size.X, (f32)size.Y, (f32)size.Z);

	m_app->getMeshFactory()->append(MeshFactory::BuiltInMesh::ROUNDED_CUBE, &m_meshbuffer, fpos, fsize);
}
