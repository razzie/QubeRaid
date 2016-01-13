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

class MaterialFactory
{
public:
	MaterialFactory(QubeRaid*);
	~MaterialFactory();
	const irr::video::SMaterial& getLineMaterial();
	const irr::video::SMaterial& getOutlineMaterial();
	const irr::video::SMaterial& getFlatShadedMaterial();
	const irr::video::SMaterial& getGroundMaterial();

private:
	QubeRaid* m_app;
	irr::video::SMaterial m_line;
	irr::video::SMaterial m_outline;
	irr::video::SMaterial m_flat;
	irr::video::SMaterial m_ground;
};
