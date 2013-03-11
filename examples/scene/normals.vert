#version 420

layout(location=1) in vec4 Normal;

out vec3 vt_NormalWs, vt_NormalOs;


uniform mat4 ModelMatrix;

void normals(){
	vt_NormalOs = Normal.xyz;
	vt_NormalWs = vec4(inverse(transpose(ModelMatrix)) * Normal).xyz;
}