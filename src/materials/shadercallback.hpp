/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class ShaderCallback : public irr::video::IShaderConstantSetCallBack
{
public:
	ShaderCallback(irr::scene::ISceneManager* smgr) : m_smgr(smgr)
	{
	}

	virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData)
	{
		irr::video::IVideoDriver* driver = services->getVideoDriver();

		irr::core::matrix4 world = driver->getTransform(irr::video::ETS_WORLD);
		services->setVertexShaderConstant("world", world.pointer(), 16);

		irr::core::matrix4 world_view_proj;
		world_view_proj = driver->getTransform(irr::video::ETS_PROJECTION);
		world_view_proj *= driver->getTransform(irr::video::ETS_VIEW);
		world_view_proj *= driver->getTransform(irr::video::ETS_WORLD);
		services->setVertexShaderConstant("world_view_proj", world_view_proj.pointer(), 16);

		irr::scene::ICameraSceneNode* cam = m_smgr->getActiveCamera();
		irr::core::vector3df camera_normal = (cam->getPosition() - cam->getTarget()).normalize();
		services->setVertexShaderConstant("camera_normal", reinterpret_cast<irr::f32*>(&camera_normal), 3);

		irr::video::SColorf outline_color(0.f, 0.f, 0.f);
		services->setVertexShaderConstant("outline_color", reinterpret_cast<irr::f32*>(&outline_color), 4);
	}

private:
	irr::scene::ISceneManager* m_smgr;
};
