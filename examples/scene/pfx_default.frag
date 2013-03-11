#version 420

out vec4 out_Color;

in vec2 vt_TexCoords;

uniform sampler2D screenMap;

void pfx_default() {
	out_Color = texture(screenMap, vt_TexCoords);
	
}