/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#pragma once

#include <map>
#include <memory>
#include <irrlicht.h>

class QubeRaid;
class BaseMesh;

class Resources
{
public:
	enum Material
	{
		LINE,
		FLAT_SHADED,
		OUTLINE,
		GROUND
	};

	enum Mesh
	{
		CUBE,
		ROUNDED_CUBE
	};

	Resources(QubeRaid*);
	~Resources();
	const irr::video::SMaterial& getMaterial(Material);
	const BaseMesh* getMesh(Mesh);

private:
	QubeRaid* m_app;
	std::map<Material, irr::video::SMaterial> m_materials;
	std::map<Mesh, std::shared_ptr<BaseMesh>> m_meshes;
};
