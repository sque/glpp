#version 330

layout(location=0) in vec4 in_Position;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;

void position(void) {
	gl_Position = ProjectionMatrix * ModelViewMatrix * in_Position;
}