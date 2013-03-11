#version 330

layout(location=0) in	vec3	aPositionOs;
layout(location=1) in	vec4	aNormal;
layout(location=2) in	vec2	aTexCoord;

out	vec4	vtColor;
out vec2	vtTexCoord;

uniform 	mat4 	ProjModView;
void main(void) {
	gl_Position = ProjModView * vec4(aPositionOs, 1);
	vtColor = vec4(aPositionOs, 1);
	vtTexCoord = aTexCoord;
}