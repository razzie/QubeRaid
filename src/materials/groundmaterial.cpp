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
uniform mat4 world;
uniform mat4 world_view_proj;
varying vec3 pos;
varying vec3 norm;

void main(void)
{
	vec4 n = normalize(vec4(gl_Normal.x, gl_Normal.y, gl_Normal.z, 0.0));
	gl_Position = world_view_proj * (gl_Vertex - (n * 0.1));
	gl_FrontColor = gl_Color;
	pos = (world * gl_Vertex).xyz;
	norm = gl_Normal;
}
)";

static const char* ps = R"(
uniform vec3 camera_normal;
varying vec3 pos;
varying vec3 norm;

void main(void)
{
	vec3 normal = normalize(norm);
	vec3 light_normal = camera_normal;
	
	vec4 light = clamp(dot(light_normal, normal), 0.0, 1.0);
	
	gl_FragColor = (light * 0.5) + (gl_Color * 0.5);
}
)";


GroundMaterial::GroundMaterial(QubeRaid* app) :
	BaseMaterial(app, vs, ps)
{
}
