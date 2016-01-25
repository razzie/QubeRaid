/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "quberaid.hpp"
#include "level/level.hpp"
#include "level/pathfinder.hpp"
#include "nodes/quboidnode.hpp"
#include "nodes/animators/walkanimator.hpp"
#include "meshes/roundedcubemesh.hpp"

using namespace irr;


QuboidNode::QuboidNode(QubeRaid* app) :
	BaseNode(app)
{
	setOutline(true, 0xff000000);
	m_material = *app->getResources()->get<video::SMaterial>("material_ground");

	RoundedCubeMesh().append(&m_meshbuffer, { -0.25f, 0.f, -0.25f }, { 0.5f, 0.5f, 0.5f }, 0xffffffff);

	m_meshbuffer.recalculateBoundingBox();
	m_meshbuffer.setHardwareMappingHint(scene::E_HARDWARE_MAPPING::EHM_STATIC);
	m_meshbuffer.setDirty();
}

QuboidNode::~QuboidNode()
{
}

void QuboidNode::walkTo(core::vector2df pos)
{
	removeAnimators();

	std::vector<core::vector2df> path;
	if (m_app->getLevel()->getPathfinder()->getPath({ getPosition().X, getPosition().Z }, pos, path))
	{
		//core::array<core::vector3df> path3d;
		//for (auto p : path)
		//	path3d.push_back({ p.X, 0.f, p.Y });

		//scene::ISceneNodeAnimator* anim = m_app->getSceneManager()->createFollowSplineAnimator(0, path3d, 3.f, 0.5f, false, false);
		scene::ISceneNodeAnimator* anim = new WalkAnimator(this, path);
		addAnimator(anim);
		anim->drop();
	}
}
