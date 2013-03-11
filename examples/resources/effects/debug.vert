#version 420

out vec4 dbg_Color;

uniform mat4 ModelViewMatrix;

uniform mat4 ProjectionMatrix;
void debug(void) {
	vec4 in_Pos = inverse( ModelViewMatrix) * inverse(ProjectionMatrix) * gl_Position;
	
	dbg_Color = sin(in_Pos);
}