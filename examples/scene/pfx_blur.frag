#version 420

out vec4 out_Color;

in vec2 vt_TexCoords;

uniform sampler2D screenMap;

const float blurSize = 1.0/512.0;

void pfx_blur() {

	vec4 sum = vec4(0.0);
 
	// blur in y (vertical)
	// take nine samples, with the distance blurSize between them
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y - 4.0*blurSize)) * 0.05;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y - 3.0*blurSize)) * 0.09;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y - 2.0*blurSize)) * 0.12;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y - blurSize)) * 0.15;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y)) * 0.16;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y + blurSize)) * 0.15;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y + 2.0*blurSize)) * 0.12;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y + 3.0*blurSize)) * 0.09;
	sum += texture(screenMap, vec2(vt_TexCoords.x, vt_TexCoords.y + 4.0*blurSize)) * 0.05;
		
	out_Color = sum;
}