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

class NodeBase : public irr::scene::ISceneNode
{
public:
	NodeBase(QubeRaid*, irr::scene::ISceneNode* parent = nullptr);
	virtual ~NodeBase();
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
	void setOutline(bool, irr::video::SColor = 0xff000000);

protected:
	QubeRaid* m_app;
	irr::video::SMaterial m_material;
	irr::scene::CVertexBuffer m_vertices;
	irr::scene::CIndexBuffer m_indices;
	irr::scene::CDynamicMeshBuffer m_meshbuffer;
	irr::video::SColor m_outline_color;
	bool m_outline;
};
