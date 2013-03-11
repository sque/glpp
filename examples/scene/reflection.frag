#version 420

out vec4 out_Color;

in vec3 vt_EyeOs;

vec3 NormalOs;

uniform samplerCube enviromentMap;
uniform vec3 CameraPosition;

void reflection(void) {
	vec3 refl = normalize(reflect(vt_EyeOs, NormalOs));
	out_Color += texture(enviromentMap, refl);
}