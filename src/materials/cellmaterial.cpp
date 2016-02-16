/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/cellmaterial.hpp"

using namespace irr;


static const char* vs = R"(
#version 110
uniform mat4 world;
uniform mat4 world_view_proj;
varying vec3 pos;
varying vec3 norm;

void main(void)
{
	gl_Position = world_view_proj * gl_Vertex;
	gl_FrontColor = gl_Color;
	pos = (world * gl_Vertex).xyz;
	norm = gl_Normal.xyz;
}
)";

static const char* ps = R"(
#version 110
uniform vec3 camera_position;
varying vec3 pos;
varying vec3 norm;

void main(void)
{
	vec3 normal = normalize(norm);
	vec3 light_normal = normalize(camera_position - pos);
	float light = floor(clamp(dot(light_normal, normal), 0.0, 1.0) * 4.0) / 4.0;
	gl_FragColor = (vec4(light) * 0.2) + (gl_Color * 0.8);
}
)";


CellMaterial::CellMaterial(Application* app) :
	BaseMaterial(app, vs, ps)
{
}
