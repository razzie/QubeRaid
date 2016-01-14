/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include "meshes/imesh.hpp"

class RoundedCubeMesh : public IMesh
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
	const irr::video::S3DVertex m_vertices[24] =
	{
		// top
		irr::video::S3DVertex(0.2f, 1.0f, 0.2f,  0.0f, 1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 1.0f, 0.2f,  0.0f, 1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 1.0f, 0.8f,  0.0f, 1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.2f, 1.0f, 0.8f,  0.0f, 1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		// upper body
		irr::video::S3DVertex(0.2f, 0.8f, 0.0f,  0.0f, 0.0f, -1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.8f, 0.0f,  0.0f, 0.0f, -1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(1.0f, 0.8f, 0.2f,  1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(1.0f, 0.8f, 0.8f,  1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.2f, 0.8f, 1.0f,  0.0f, 0.0f, 1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.0f, 0.8f, 0.8f,  -1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.0f, 0.8f, 0.2f,  -1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		// lower body
		irr::video::S3DVertex(0.2f, 0.2f, 0.0f,  0.0f, 0.0f, -1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.2f, 0.0f,  0.0f, 0.0f, -1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(1.0f, 0.2f, 0.2f,  1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(1.0f, 0.2f, 0.8f,  1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.2f, 1.0f,  0.0f, 0.0f, 1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.2f, 0.2f, 1.0f,  0.0f, 0.0f, 1.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.0f, 0.2f, 0.8f,  -1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.0f, 0.2f, 0.2f,  -1.0f, 0.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		// bottom
		irr::video::S3DVertex(0.2f, 0.0f, 0.2f,  0.0f, -1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.0f, 0.2f,  0.0f, -1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.8f, 0.0f, 0.8f,  0.0f, -1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
		irr::video::S3DVertex(0.2f, 0.0f, 0.8f,  0.0f, -1.0f, 0.0f,  0xffffffff,  0.f, 0.f),
	};

	const irr::u16 m_indices[132] =
	{
		// top
		0, 2, 1, 0, 3, 2,
		// upper body
		4, 1, 5, 4, 0, 1,
		5, 1, 6,
		1, 7, 6, 1, 2, 7,
		2, 8, 7,
		3, 8, 2, 3, 9, 8,
		3, 10, 9,
		11, 3, 0, 11, 10, 3,
		0, 4, 11,
		// body
		5, 12, 4, 5, 13, 12,
		6, 13, 5, 6, 14, 13,
		7, 14, 6, 7, 15, 14,
		8, 15, 7, 8, 16, 15,
		9, 16, 8, 9, 17, 16,
		10, 17, 9, 10, 18, 17,
		11, 18, 10, 11, 19, 18,
		4, 19, 11, 4, 12, 19,
		// lower body
		12, 13, 21, 12, 21, 20,
		13, 14, 21,
		21, 14, 15, 21, 15, 22,
		22, 15, 16,
		23, 22, 16, 23, 16, 17,
		23, 17, 18,
		19, 20, 23, 19, 23, 18,
		20, 19, 12,
		// bottom
		20, 21, 22, 20, 22, 23
	};
};
