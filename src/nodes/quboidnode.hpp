/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>
#include "nodes/basenode.hpp"

class QubeRaid;
class Level;

class QuboidNode : public BaseNode
{
public:
	QuboidNode(QubeRaid*);
	virtual ~QuboidNode();
	void walkTo(irr::core::vector2df pos);
};
