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

using namespace irr;


MaterialFactory::MaterialFactory(QubeRaid* app) :
	m_app(app)
{
	scene::ISceneManager* smgr = m_app->getSceneManager();
	video::IGPUProgrammingServices* gpu = smgr->getVideoDriver()->getGPUProgrammingServices();
	ShaderCallback* shader_cb = new ShaderCallback(smgr);
	s32 mat_type;

	// initialize line material
	m_line.ZBuffer = false;
	m_line.Lighting = false;
	m_line.Thickness = 2.f;

	// initialize outline material
	mat_type = gpu->addHighLevelShaderMaterialFromFiles(
		"../assets/shaders/outline.vert", "main", video::EVST_VS_1_1,
		"../assets/shaders/outline.frag", "main", video::EPST_PS_1_1,
		shader_cb);
	m_outline.MaterialType = (video::E_MATERIAL_TYPE)mat_type;
	m_outline.FrontfaceCulling = true;
	m_outline.BackfaceCulling = false;
	m_outline.ZBuffer = video::ECFN_NEVER;

	// initialize flat shaded material
	mat_type = gpu->addHighLevelShaderMaterialFromFiles(
		"../assets/shaders/flat.vert", "main", video::EVST_VS_1_1,
		"../assets/shaders/flat.frag", "main", video::EPST_PS_1_1,
		shader_cb);
	m_flat.MaterialType = (video::E_MATERIAL_TYPE)mat_type;

	// initialize ground material
	mat_type = gpu->addHighLevelShaderMaterialFromFiles(
		"../assets/shaders/ground.vert", "main", video::EVST_VS_1_1,
		"../assets/shaders/ground.frag", "main", video::EPST_PS_1_1,
		shader_cb);
	m_ground.MaterialType = (video::E_MATERIAL_TYPE)mat_type;
}

MaterialFactory::~MaterialFactory()
{
}

const video::SMaterial& MaterialFactory::getLineMaterial()
{
	return m_line;
}

const video::SMaterial& MaterialFactory::getOutlineMaterial()
{
	return m_outline;
}

const video::SMaterial& MaterialFactory::getFlatShadedMaterial()
{
	return m_flat;
}

const video::SMaterial& MaterialFactory::getGroundMaterial()
{
	return m_ground;
}
