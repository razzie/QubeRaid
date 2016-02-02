/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <vector>
#include <irrlicht.h>
#include "nodes/basenode.hpp"
#include "level/level.hpp" // Level::GroundBlock

class QubeRaid;

class GroundNode : public BaseNode
{
public:
	GroundNode(QubeRaid*, const std::vector<Level::GroundBlock>& blocks);
	virtual ~GroundNode();

	static irr::f32 getHeight(irr::core::vector2df pos);

private:
	void addBlock(const Level::GroundBlock&);
};
