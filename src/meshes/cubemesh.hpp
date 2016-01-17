/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include "meshes/basemesh.hpp"

class CubeMesh : public BaseMesh
{
public:
	const irr::video::S3DVertex* getVertices() const
	{
		return m_vertices;
	}

	size_t getVertexCount() const
	{
		return sizeof(m_vertices) / sizeof(irr::video::S3DVertex);
	}

	const irr::u16* getIndices() const
	{
		return m_indices;
	}

	size_t getIndexCount() const
	{
		return sizeof(m_indices) / sizeof(irr::u16);
	}

private:
	const irr::video::S3DVertex m_vertices[8] =
	{
		// top - upper left
		irr::video::S3DVertex(0.f, 1.f, 0.f,  -0.5f, 0.5f, -0.5f,  0xffffffff,  0.f, 0.f),
		// top - upper right
		irr::video::S3DVertex(1.f, 1.f, 0.f,  0.5f, 0.5f, -0.5f,  0xffffffff,  0.f, 0.f),
		// top - lower right
		irr::video::S3DVertex(1.f, 1.f, 1.f,  0.5f, 0.5f, 0.5f,  0xffffffff,  0.f, 0.f),
		// top - lower left
		irr::video::S3DVertex(0.f, 1.f, 1.f,  -0.5f, 0.5f, 0.5f,  0xffffffff,  0.f, 0.f),
		// bottom - upper left
		irr::video::S3DVertex(0.f, 0.f, 0.f,  -0.5f, -0.5f, -0.5f,  0xffffffff,  0.f, 0.f),
		// bottom - upper right
		irr::video::S3DVertex(1.f, 0.f, 0.f,  0.5f, -0.5f, -0.5f,  0xffffffff,  0.f, 0.f),
		// bottom - lower right
		irr::video::S3DVertex(1.f, 0.f, 1.f,  0.5f, -0.5f, 0.5f,  0xffffffff,  0.f, 0.f),
		// bottom - lower left
		irr::video::S3DVertex(0.f, 0.f, 1.f,  -0.5f, -0.5f, 0.5f,  0xffffffff,  0.f, 0.f)
	};

	const irr::u16 m_indices[36] =
	{
		// top
		0, 2, 1, 0, 3, 2,
		// front
		3, 6, 2, 3, 7, 6,
		// back
		1, 4, 0, 1, 5, 4,
		// left
		0, 7, 3, 0, 4, 7,
		// right
		2, 5, 1, 2, 6, 5,
		// bottom
		4, 5, 6, 4, 6, 7
	};
};
