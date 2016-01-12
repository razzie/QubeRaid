/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class QubeRaid;

class GroundNode : public irr::scene::ISceneNode
{
public:
	GroundNode(QubeRaid*);
	virtual ~GroundNode();
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);

private:
	QubeRaid* m_app;
	irr::video::SMaterial m_material;
	irr::scene::CVertexBuffer m_vertices;
	irr::scene::CIndexBuffer m_indices;
	irr::scene::CDynamicMeshBuffer m_meshbuffer;

	void addCube(irr::core::vector3di pos, irr::core::vector3di size = { 1,1,1 });
};
