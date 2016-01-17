/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

#include "materials/flatmaterial.hpp"

using namespace irr;


static const char* vs = "\
uniform mat4 world;\
uniform mat4 world_view_proj;\
varying vec3 pos;\
\
void main(void)\
{\
	gl_Position = world_view_proj * gl_Vertex;\
	gl_FrontColor = gl_Color;\
	pos = (world * gl_Vertex).xyz;\
}";

static const char* ps = "\
uniform vec3 camera_pos;\
uniform vec3 light_pos;\
uniform vec4 light_color;\
varying vec3 pos;\
\
void main(void)\
{\
	vec3 normal = normalize(cross(dFdy(pos), dFdx(pos)));\
	vec3 light_normal = normalize(camera_pos);\
	vec4 light = clamp(light_color * dot(light_normal, normal), 0.0, 1.0);\
	gl_FragColor = gl_Color * light;\
}";


FlatMaterial::FlatMaterial(QubeRaid* app) :
	BaseMaterial(app, vs, ps)
{
}
