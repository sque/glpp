#version 420

vec3 NormalOs, NormalWs;

out vec4 out_Color;

void debug_normals(){
	out_Color = vec4(NormalWs, 1);
}