/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include <random>
#include "meshes/basemesh.hpp"

using namespace irr;


void BaseMesh::append(scene::IDynamicMeshBuffer* buf, core::vector3df translate, core::vector3df scale, irr::video::SColor color, f32 randomize) const
{
	size_t vertex_count = this->getVertexCount();
	auto* src_vertices = this->getVertices();
	auto& dest_vertices = buf->getVertexBuffer();

	size_t index_count = this->getIndexCount();
	u16 base_index = buf->getVertexCount();
	auto* src_indices = this->getIndices();
	auto& dest_indices = buf->getIndexBuffer();

	if (randomize > 0.f)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<f32> dis(-randomize, randomize);

		for (size_t i = 0; i < vertex_count; ++i)
		{
			auto v = src_vertices[i];
			v.Pos *= scale;
			v.Pos += translate;
			v.Pos += {dis(gen), dis(gen), dis(gen)};
			v.Color = color;
			dest_vertices.push_back(v);
		}
	}
	else
	{
		for (size_t i = 0; i < vertex_count; ++i)
		{
			auto v = src_vertices[i];
			v.Pos *= scale;
			v.Pos += translate;
			v.Color = color;
			dest_vertices.push_back(v);
		}
	}

	for (size_t i = 0; i < index_count; ++i)
	{
		dest_indices.push_back(src_indices[i] + base_index);
	}
}
