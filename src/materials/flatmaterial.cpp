/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/flatmaterial.hpp"

using namespace irr;


static const char* vs = R"(
#version 110
uniform mat4 world;
uniform mat4 world_view_proj;
varying vec3 pos;

void main(void)
{
	gl_Position = world_view_proj * gl_Vertex;
	gl_FrontColor = gl_Color;
	pos = (world * gl_Vertex).xyz;
}
)";

static const char* ps = R"(
#version 110
uniform vec3 camera_position;
varying vec3 pos;

void main(void)
{
	vec3 normal = normalize(cross(dFdy(pos), dFdx(pos)));
	vec3 light_normal = normalize(camera_position - pos);
	vec4 light = vec4(clamp(dot(light_normal, normal), 0.0, 1.0));
	gl_FragColor = gl_Color * light;
}
)";


FlatMaterial::FlatMaterial(Application* app) :
	BaseMaterial(app, vs, ps)
{
}
