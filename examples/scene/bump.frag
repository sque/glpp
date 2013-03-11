#version 420


in vec3 vt_TexCoord, vt_Normal, vt_Tangent, vt_BiTangent;

vec3 NormalWs, NormalOs;

uniform sampler2D bumpMap;
uniform mat4 ModelMatrix;

void bump(){
	mat3 TBN = transpose(mat3(
		normalize(vt_Tangent),
		normalize(vt_Normal),
		normalize(vt_BiTangent)
	));
	NormalOs = normalize(TBN * texture(bumpMap, vt_TexCoord.st).xyz);
	NormalWs = vec4(normalize(inverse(transpose(ModelMatrix)) * vec4(NormalOs, 1))).xyz;
}