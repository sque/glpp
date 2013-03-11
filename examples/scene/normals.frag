#version 420

in vec3 vt_NormalWs, vt_NormalOs;

vec3 NormalWs, NormalOs;

void normals(){
	NormalWs = normalize(vt_NormalWs);
	NormalOs = normalize(vt_NormalOs);
}