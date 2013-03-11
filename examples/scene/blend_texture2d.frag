#version 420

in vec3 vt_TexCoord;
out vec4 out_Color;
uniform sampler2D blendTexture2dMap;

void blend_texture2d() {
	out_Color *= texture(blendTexture2dMap, vt_TexCoord.st);
}