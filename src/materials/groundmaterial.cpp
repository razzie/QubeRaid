/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/groundmaterial.hpp"

using namespace irr;


static const char* vs = R"(
#version 110
uniform mat4 world;
uniform mat4 world_view_proj;
varying vec3 norm;

void main(void)
{
	vec4 n = normalize(vec4(gl_Normal, 0.0));
	gl_Position = world_view_proj * (gl_Vertex - (n * 0.1));
	gl_FrontColor = gl_Color;
	norm = gl_Normal;
}
)";

static const char* ps = R"(
#version 110
uniform vec3 camera_normal;
varying vec3 norm;

void main(void)
{
	vec3 normal = normalize(norm);
	vec3 light_normal = camera_normal;
	vec4 light = vec4(clamp(dot(light_normal, normal), 0.0, 1.0));
	gl_FragColor = (light * 0.25) + (gl_Color * 0.75);
}
)";


GroundMaterial::GroundMaterial(QubeRaid* app) :
	BaseMaterial(app, vs, ps)
{
}
