#version 330


uniform 	sampler2D 	colorMap;

in	vec4	vtColor;
in	vec2	vtTexCoord;

out vec4	outColor;

void main(void) {
	outColor = texture(colorMap, vtTexCoord);
	
}