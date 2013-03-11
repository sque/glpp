#version 420

uniform samplerCube skyCubeMap;

in vec3 vt_TexCoord;
out vec4 out_Color;

void main(void) {

	out_Color = texture(skyCubeMap, vt_TexCoord);
}