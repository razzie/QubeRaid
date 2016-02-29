/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <cstdint>
#include <irrlicht.h>
#include "nodes/basenode.hpp"

class Application;

class TerrainNode : public BaseNode
{
public:
	TerrainNode(Application*, uint32_t seed, irr::core::dimension2du size);
	virtual ~TerrainNode();

private:
};
