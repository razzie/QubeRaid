/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/shadercallback.hpp"

using namespace irr;


ShaderCallback::ShaderCallback(scene::ISceneManager* smgr) :
	m_smgr(smgr)
{
}

ShaderCallback::~ShaderCallback()
{
}

void ShaderCallback::OnSetMaterial(const video::SMaterial& material)
{
	m_outline = video::SColor(*reinterpret_cast<const u32*>(&material.MaterialTypeParam));
}

void ShaderCallback::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
	video::IVideoDriver* driver = services->getVideoDriver();

	core::matrix4 world = driver->getTransform(video::ETS_WORLD);
	services->setVertexShaderConstant("world", world.pointer(), 16);

	core::matrix4 world_view_proj;
	world_view_proj = driver->getTransform(video::ETS_PROJECTION);
	world_view_proj *= driver->getTransform(video::ETS_VIEW);
	world_view_proj *= driver->getTransform(video::ETS_WORLD);
	services->setVertexShaderConstant("world_view_proj", world_view_proj.pointer(), 16);

	scene::ICameraSceneNode* cam = m_smgr->getActiveCamera();
	core::vector3df camera_position = cam->getPosition();
	core::vector3df camera_normal = (camera_position - cam->getTarget()).normalize();
	services->setVertexShaderConstant("camera_position", reinterpret_cast<f32*>(&camera_position), 3);
	services->setVertexShaderConstant("camera_normal", reinterpret_cast<f32*>(&camera_normal), 3);

	f32 time = 0.001f * (f32)m_timer.peekElapsed();
	services->setVertexShaderConstant("time", reinterpret_cast<f32*>(&time), 1);

	services->setVertexShaderConstant("outline_color", reinterpret_cast<f32*>(&m_outline), 4);
}
