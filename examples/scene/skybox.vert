#version 420

layout(location=0) in vec4 in_Position;
layout(location=2) in vec4 in_TexCoord;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

out vec3 vt_TexCoord;

void main(void) {
	mat4 RotationMatrix = ViewMatrix;
	RotationMatrix[3][0] = 0;
	RotationMatrix[3][1] = 0;
	RotationMatrix[3][2] = 0;
	
	gl_Position = ProjectionMatrix * RotationMatrix * in_Position;
	//gl_Position = ProjectionMatrix * ViewMatrix * in_Position;
	vt_TexCoord = in_TexCoord.xyz;
}