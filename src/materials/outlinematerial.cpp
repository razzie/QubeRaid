/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/outlinematerial.hpp"

using namespace irr;


static const char* vs = R"(
#version 110
uniform mat4 world_view_proj;

void main(void)
{
	vec4 norm = normalize(vec4(gl_Normal, 0.0));
	gl_Position = world_view_proj * (gl_Vertex + (norm * 0.1));
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


OutlineMaterial::OutlineMaterial(QubeRaid* app) :
	BaseMaterial(app, vs, ps)
{
	FrontfaceCulling = true;
	BackfaceCulling = false;
	//ZBuffer = video::ECFN_NEVER;
}
