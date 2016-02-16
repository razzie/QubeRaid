/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class Application;

class BaseMaterial : public irr::video::SMaterial
{
public:
	BaseMaterial(Application*, const char* vs, const char* ps, irr::video::IShaderConstantSetCallBack* = nullptr);
	~BaseMaterial();
};
