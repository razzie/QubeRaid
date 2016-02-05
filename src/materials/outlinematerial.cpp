/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/outlinematerial.hpp"
#include "materials/shadercallback.hpp"
#include "quberaid.hpp"

using namespace irr;


static const char* vs = R"(
#version 110
uniform mat4 world;
uniform mat4 world_view_proj;
uniform vec3 camera_position;
uniform float outline_offset;
uniform float outline_thickness;

void main(void)
{
	vec3 pos = (world * gl_Vertex).xyz;
	vec4 norm = normalize(vec4(gl_Normal.xyz, 0.0));
	float factor = distance(pos, camera_position) * 0.0075;

	vec4 scale = norm * factor * outline_thickness;
	vec4 translation = normalize(vec4(pos - camera_position, 0.0)) * outline_offset;

	gl_Position = world_view_proj * (gl_Vertex + scale + translation);
}
)";

static const char* ps = R"(
#version 110
uniform vec4 outline_color;

void main(void)
{
	gl_FragColor = outline_color;
}
)";

class OutlineShaderCallback : public ShaderCallback
{
public:
	OutlineShaderCallback(scene::ISceneManager* smgr) :
		ShaderCallback(smgr)
	{
	}

	virtual ~OutlineShaderCallback() = default;

	virtual void OnSetMaterial(const video::SMaterial& material)
	{
		m_color = video::SColor(*reinterpret_cast<const u32*>(&material.MaterialTypeParam));
		m_offset = material.MaterialTypeParam2;
		m_thickness = material.Thickness;
	}

	virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
	{
		ShaderCallback::OnSetConstants(services, userData);

		services->setVertexShaderConstant("outline_color", reinterpret_cast<f32*>(&m_color), 4);
		services->setVertexShaderConstant("outline_offset", &m_offset, 1);
		services->setVertexShaderConstant("outline_thickness", &m_thickness, 1);
	}

private:
	irr::video::SColorf m_color;
	irr::f32 m_offset;
	irr::f32 m_thickness;
};


OutlineMaterial::OutlineMaterial(QubeRaid* app) :
	BaseMaterial(app, vs, ps, new OutlineShaderCallback(app->getSceneManager()))
{
	FrontfaceCulling = true;
	BackfaceCulling = false;
	//ZBuffer = video::ECFN_NEVER;
}
