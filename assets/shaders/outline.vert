/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

uniform mat4 world;
uniform mat4 world_view_proj;
varying vec3 pos;

void main(void)
{
	vec4 norm = normalize(vec4(gl_Normal.x, gl_Normal.y, gl_Normal.z, 0.0));
	gl_Position = world_view_proj * (gl_Vertex + (norm * 0.1));
	//gl_FrontColor = gl_Color;
	//pos = (world * gl_Vertex).xyz;
}
