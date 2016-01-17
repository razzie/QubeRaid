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

class BaseMaterial : public irr::video::SMaterial
{
public:
	BaseMaterial(QubeRaid*, const char* vs, const char* ps);
	~BaseMaterial();
};
