/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <functional>

template<class T>
class Grid3D
{
public:
	Grid3D(size_t width, size_t height, size_t depth) :
		m_width(width),
		m_height(height),
		m_depth(depth)
	{
		m_grid = new T[m_width * m_height * m_depth];
	}

	~Grid3D()
	{
		delete[] m_grid;
	}

	T* operator()(int x, int y, int z)
	{
		if (x < 0 || x >= (int)m_width ||
			y < 0 || y >= (int)m_height ||
			z < 0 || z >= (int)m_depth)
		{
			return nullptr;
		}

		return &m_grid[(x * m_height * m_depth) + (y * m_depth) + z];
	}

	const T* operator()(int x, int y, int z) const
	{
		if (x < 0 || x >= (int)m_width ||
			y < 0 || y >= (int)m_height ||
			z < 0 || z >= (int)m_depth)
		{
			return nullptr;
		}

		return &m_grid[(x * m_height * m_depth) + (y * m_depth) + z];
	}

	void foreach(std::function<void(T*,int,int,int)> f)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			for (size_t y = 0; y < m_height; ++y)
			{
				for (size_t z = 0; z < m_depth; ++z)
				{
					f((*this)(x, y, z), x, y, z);
				}
			}
		}
	}

	void foreach(std::function<void(const T*, int, int, int)> f) const
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			for (size_t y = 0; y < m_height; ++y)
			{
				for (size_t z = 0; z < m_depth; ++z)
				{
					f((*this)(x, y, z), x, y, z);
				}
			}
		}
	}

private:
	size_t m_width;
	size_t m_height;
	size_t m_depth;
	T* m_grid;
};
