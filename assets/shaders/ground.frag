/**
 * Copyright (c) 2016 Gábor Görzsöny (www.gorzsony.com)
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

/*
float rand2(vec3 n)
{
    return fract(sin(dot(n.xyz, vec3(10, 300, 400)))* 43758.5453);
}

float interp_rand2(vec3 n, float gs)
{
    vec3 l = floor(n * gs) / gs;
    vec3 r = (floor(n * gs)+1.) / gs;

    vec3 f = 1. - (r - n) * gs;

    float p000 = rand2(vec3(l.x, l.y, l.z));
    float p001 = rand2(vec3(l.x, l.y, r.z));
    float p010 = rand2(vec3(l.x, r.y, l.z));
    float p011 = rand2(vec3(l.x, r.y, r.z));
    float p100 = rand2(vec3(r.x, l.y, l.z));
    float p101 = rand2(vec3(r.x, l.y, r.z));
    float p110 = rand2(vec3(r.x, r.y, l.z));
    float p111 = rand2(vec3(r.x, r.y, r.z));

    float c = mix(mix(mix(p000, p100, f.x),
                      mix(p001, p101, f.x),
                      f.z),
                  mix(mix(p010, p110, f.x),
                      mix(p011, p111, f.x),
                      f.z),
                  f.y);

    return c;
}

float rand(vec3 n, float dist)
{
    float c0 = interp_rand2(n, 100.);
    float c1 = interp_rand2(n, 1000.);
    float c2 = interp_rand2(n, 7000.);

    float c = mix(c1, c0, dist);

    c = mix(c2, c, min(1.,dist*4.));

    return 3. * ((c * 0.5) + 0.5);
}
*/

void main(void)
{
	vec3 normal = normalize(norm);
	vec3 flat_normal = normalize(cross(dFdy(pos), dFdx(pos)));
	vec3 light_normal = normalize(camera_pos);

	vec4 color = vec4(0.5, 0.5, 0.375, 0.0);
	vec4 light = clamp(light_color * dot(light_normal, normal), 0.0, 1.0);

	gl_FragColor = light;
}
