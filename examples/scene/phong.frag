

in float att_factor[MAX_LIGHTS];
in vec3 vt_LightDirWs[MAX_LIGHTS], vt_EyeVecWs;

out vec4 out_Color;

vec3 NormalWs;

vec4 compute_light(light_t light, vec3 N, vec3 L, float att_factor) {
	vec4 sh_Color = mat.emission + mat.ambient * ambient;
	float lambertTerm = dot(N, L);

	if (lambertTerm > 0) {
		sh_Color += light.diffuse * mat.diffuse * lambertTerm * att_factor;
		vec3 E = normalize(vt_EyeVecWs);
		vec3 R = reflect(-L, N);
		float spec_factor = pow( max(dot(R, E), 0.0), mat.shininess );
		sh_Color += light.specular * mat.specular * spec_factor * att_factor;
	}
	return sh_Color;
}

uniform sampler2D colorMap;

void phong(void){
	
	vec4 sh_Color = vec4(0,0,0,1);
	vec3 N = normalize(NormalWs);

	vec3 L = normalize(vt_LightDirWs[0]);
	sh_Color += compute_light(light[0], N, L, att_factor[0]);
	L = normalize(vt_LightDirWs[1]);
	sh_Color += compute_light(light[1], N, L, att_factor[1]);

	out_Color += sh_Color;

}
