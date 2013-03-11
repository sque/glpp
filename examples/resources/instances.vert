#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
in int gl_InstanceID;
out vec4 ex_Color;
out float ex_Test;
uniform mat4 ProjectionMatrix;
uniform float Time;


void main(void)
{
	float t = gl_InstanceID;
	t = Time + ((gl_InstanceID/ 20)/10);
	vec4 nPosition = in_Position;
	if (nPosition.y > 0 ) {
		nPosition.z += sin(t);
	}
	gl_Position = ProjectionMatrix * (nPosition + vec4(gl_InstanceID % 20, 0, (-gl_InstanceID / 20) + ((gl_InstanceID %2)*1), 0));
	
	
	ex_Test = in_Position[0];
	ex_Color = in_Color;
}
