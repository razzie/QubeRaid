/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include "meshes/imesh.hpp"

class QubeRaid;

class MeshFactory
{
public:
	enum BuiltInMesh
	{
		CUBE,
		ROUNDED_CUBE
	};

	MeshFactory(QubeRaid*);
	~MeshFactory();
	void append(const IMesh*, irr::scene::IDynamicMeshBuffer*,
				irr::core::vector3df translate, irr::core::vector3df scale,
				irr::video::SColor color = 0xffffffff, irr::f32 randomize = 0.f) const;
	void append(BuiltInMesh, irr::scene::IDynamicMeshBuffer*,
				irr::core::vector3df translate, irr::core::vector3df scale,
				irr::video::SColor color = 0xffffffff, irr::f32 randomize = 0.f) const;

private:
	QubeRaid* m_app;
};
