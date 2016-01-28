/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/basematerial.hpp"
#include "materials/shadercallback.hpp"
#include "quberaid.hpp"

using namespace irr;


BaseMaterial::BaseMaterial(QubeRaid* app, const char* vs, const char* ps)
{
	scene::ISceneManager* smgr = app->getSceneManager();
	video::IGPUProgrammingServices* gpu = smgr->getVideoDriver()->getGPUProgrammingServices();
	ShaderCallback* shader_cb = new ShaderCallback(smgr);

	MaterialType = (video::E_MATERIAL_TYPE)gpu->addHighLevelShaderMaterial(
		(const c8*)vs, "main", video::EVST_VS_2_0,
		(const c8*)ps, "main", video::EPST_PS_2_0,
		shader_cb);
}

BaseMaterial::~BaseMaterial()
{
}
