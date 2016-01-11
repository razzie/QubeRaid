/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "utils/shadercallback.hpp"
#include "utils/materialfactory.hpp"
#include "quberaid.hpp"


MaterialFactory::MaterialFactory(QubeRaid* app) :
	m_app(app)
{
	irr::video::IGPUProgrammingServices* gpu = m_app->getSceneManager()->getVideoDriver()->getGPUProgrammingServices();
	ShaderCallback* shader_cb;
	irr::s32 mat_type;

	// initialize line material
	m_line_mat.ZBuffer = false;
	m_line_mat.Lighting = false;
	m_line_mat.Thickness = 2.f;

	// initialize flat shaded material
	shader_cb = new ShaderCallback(m_app->getSceneManager());
	mat_type = gpu->addHighLevelShaderMaterialFromFiles(
		"../assets/shaders/flat.vert", "main", irr::video::EVST_VS_1_1,
		"../assets/shaders/flat.frag", "main", irr::video::EPST_PS_1_1,
		shader_cb);
	m_flat_mat.MaterialType = (irr::video::E_MATERIAL_TYPE)mat_type;

	// initialize surface material
	shader_cb = new ShaderCallback(m_app->getSceneManager());
	mat_type = gpu->addHighLevelShaderMaterialFromFiles(
		"../assets/shaders/surface.vert", "main", irr::video::EVST_VS_1_1,
		"../assets/shaders/surface.frag", "main", irr::video::EPST_PS_1_1,
		shader_cb);
	m_surface_mat.MaterialType = (irr::video::E_MATERIAL_TYPE)mat_type;
}

MaterialFactory::~MaterialFactory()
{
}

const irr::video::SMaterial& MaterialFactory::getLineMaterial()
{
	return m_line_mat;
}

const irr::video::SMaterial& MaterialFactory::getSurfaceMaterial()
{
	return m_surface_mat;
}
