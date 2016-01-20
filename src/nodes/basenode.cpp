/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "quberaid.hpp"
#include "nodes/basenode.hpp"

using namespace irr;

BaseNode::BaseNode(QubeRaid* app, scene::ISceneNode* parent) :
	scene::ISceneNode(parent ? parent : app->getSceneManager()->getRootSceneNode(), app->getSceneManager()),
	m_app(app),
	m_vertices(video::EVT_STANDARD),
	m_indices(video::EIT_16BIT),
	m_meshbuffer(video::EVT_STANDARD, video::EIT_16BIT),
	m_outline_material(*app->getResources()->get<video::SMaterial>("material_outline")),
	m_outline_color(0xff000000),
	m_outline(false)
{
	m_meshbuffer.setVertexBuffer(&m_vertices);
	m_meshbuffer.setIndexBuffer(&m_indices);
}

BaseNode::~BaseNode()
{
}

void BaseNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);

	ISceneNode::OnRegisterSceneNode();
}

void BaseNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

	if (m_outline)
	{
		driver->setMaterial(m_outline_material);
		driver->drawMeshBuffer(&m_meshbuffer);
	}

	driver->setMaterial(m_material);
	driver->drawMeshBuffer(&m_meshbuffer);
}

const core::aabbox3d<f32>& BaseNode::getBoundingBox() const
{
	return m_meshbuffer.getBoundingBox();
}

u32 BaseNode::getMaterialCount() const
{
	return 1;
}

video::SMaterial& BaseNode::getMaterial(u32 i)
{
	return m_material;
}

void BaseNode::setOutline(bool enabled, video::SColor color)
{
	m_outline = enabled;
	m_outline_color = color;
}
