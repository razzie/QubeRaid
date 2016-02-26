/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <irrlicht.h>
#include "utils/grid.hpp"

class MarchingCubes
{
public:
	MarchingCubes(size_t width, size_t height, size_t depth);
	~MarchingCubes();
	Grid3D<float>& getGrid();
	const Grid3D<float>& getGrid() const;
	void build(irr::scene::IDynamicMeshBuffer*, bool weld = false) const;

private:
	struct Cell
	{
		irr::core::vector3df pos[8];
		float value[8];

		void set(size_t n, const Grid3D<float>& grid, int x, int y, int z)
		{
			const float* v;
			const float dummy_val = 0.f;
#pragma warning( push )
#pragma warning( disable : 4244 )
			pos[n].set(x, y, z);
			value[n] = *((v = grid(x, y, z)) ? v : &dummy_val);
#pragma warning( pop )
		}
	};

	void fillCell(Cell&, int x, int y, int z) const;
	static void addCell(const Cell&, irr::scene::IDynamicMeshBuffer*, bool weld = false);
	static int findVertex(irr::core::vector3df, const irr::scene::IDynamicMeshBuffer*);
	static irr::core::vector3df interpolate(irr::core::vector3df a_pos, irr::core::vector3df b_pos, float a_val, float b_val);

	Grid3D<float> m_grid;
};
