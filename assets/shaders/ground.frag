/**
 * Copyright (c) 2016 G�bor G�rzs�ny (www.gorzsony.com)
 *
 * This source is a private work and can be used only with the
 * written permission of the author. Do not redistribute it!
 * All rights reserved.
 */

uniform vec3 camera_pos;
uniform vec3 light_pos;
uniform vec4 light_color;
varying vec3 pos;
varying vec3 norm;

void main(void)
{
	vec3 normal = normalize(norm);
	vec3 light_normal = normalize(camera_pos);

	vec4 light = clamp(light_color * dot(light_normal, normal), 0.0, 1.0);

	gl_FragColor = (light * 0.5) + (gl_Color * 0.5);
}
