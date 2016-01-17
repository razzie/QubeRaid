/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <vector>
#include <utility> // std::pair
#include <irrlicht.h>
#include "nodes/basenode.hpp"

class QubeRaid;

class GroundNode : public BaseNode
{
public:
	GroundNode(QubeRaid*, const std::vector<std::pair<irr::core::vector3di, irr::core::vector3di>>& blocks);
	virtual ~GroundNode();

private:
	void addBlock(irr::core::vector3di pos, irr::core::vector3di size = { 1,1,1 });
};
