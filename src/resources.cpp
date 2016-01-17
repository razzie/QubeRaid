/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "resources.hpp"
#include "quberaid.hpp"
#include "materials/linematerial.hpp"
#include "materials/flatmaterial.hpp"
#include "materials/outlinematerial.hpp"
#include "materials/groundmaterial.hpp"
#include "meshes/cubemesh.hpp"
#include "meshes/roundedcubemesh.hpp"

using namespace irr;


Resources::Resources(QubeRaid* app) :
	m_app(app)
{
	m_materials.emplace<Material, LineMaterial>(Material::LINE, {});
	m_materials.emplace<Material, FlatMaterial>(Material::FLAT_SHADED, app);
	m_materials.emplace<Material, OutlineMaterial>(Material::OUTLINE, app);
	m_materials.emplace<Material, GroundMaterial>(Material::GROUND, app);

	m_meshes.emplace(Mesh::CUBE, std::make_shared<CubeMesh>());
	m_meshes.emplace(Mesh::ROUNDED_CUBE, std::make_shared<RoundedCubeMesh>());
}

Resources::~Resources()
{
}

const irr::video::SMaterial& Resources::getMaterial(Material mat)
{
	return m_materials[mat];
}

const BaseMesh* Resources::getMesh(Mesh mesh)
{
	return m_meshes[mesh].get();
}
