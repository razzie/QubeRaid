/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>

class IMesh
{
public:
	virtual ~IMesh() = default;
	virtual const irr::video::S3DVertex* getVertices() const = 0;
	virtual size_t getVertexCount() const = 0;
	virtual const irr::u16* getIndices() const = 0;
	virtual size_t getIndexCount() const = 0;
};
