#version 420

layout(location=2) in vec3 texCoord;

out vec3 vt_TexCoord;

void blend_texture2d(){
	vt_TexCoord =  texCoord;
}