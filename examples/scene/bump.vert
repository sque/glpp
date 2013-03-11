#version 420

layout(location=1) in vec4 Normal;
layout(location=2) in vec4 TexCoord;
layout(location=3) in vec4 Tangent;
layout(location=4) in vec4 BiTangent;

out vec3 vt_TexCoord;
out vec3 vt_Tangent;
out vec3 vt_BiTangent;
out vec3 vt_Normal;

void bump(){
	vt_TexCoord =  TexCoord.xyz;
	vt_Tangent = Tangent.xyz;
	vt_BiTangent = BiTangent.xyz;
	vt_Normal = Normal.xyz;
}