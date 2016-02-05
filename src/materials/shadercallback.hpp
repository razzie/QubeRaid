/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <gg/timer.hpp>
#include <irrlicht.h>

class ShaderCallback : public irr::video::IShaderConstantSetCallBack
{
public:
	ShaderCallback(irr::scene::ISceneManager* smgr);
	virtual ~ShaderCallback();
	virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData);

protected:
	irr::scene::ISceneManager* m_smgr;
	gg::Timer m_timer;
};
