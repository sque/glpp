#version 420

out vec4 out_Color;

in vec2 vt_TexCoords;

uniform sampler2D screenMap;
uniform int width=200;
uniform int height=100;


void pfx_underwater() {
	out_Color = texture(screenMap, vt_TexCoords.xy);
}
