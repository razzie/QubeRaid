/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class Application;

class BaseNode : public irr::scene::ISceneNode
{
public:
	BaseNode(Application*);
	virtual ~BaseNode();
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
	virtual irr::u32 getMaterialCount() const;
	virtual irr::video::SMaterial& getMaterial(irr::u32 i);
	void setOutline(bool, irr::f32 thickness = 1.f, irr::f32 offset = 1.f, irr::video::SColor = 0xff000000);

protected:
	Application* m_app;
	irr::scene::CVertexBuffer m_vertices;
	irr::scene::CIndexBuffer m_indices;
	irr::scene::CDynamicMeshBuffer m_meshbuffer;
	irr::video::SMaterial m_material;
	irr::video::SMaterial m_outline_material;
	bool m_outline;
};
