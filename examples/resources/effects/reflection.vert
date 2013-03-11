#version 420

layout(location=0) in vec4 in_Position;

uniform samplerCube enviromentMap;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 CameraPositionWs;

out vec3 vt_EyeOs;

void reflection(void){
	vt_EyeOs = vec4(in_Position - inverse(ModelMatrix) * vec4(CameraPositionWs,1)).xyz;
}