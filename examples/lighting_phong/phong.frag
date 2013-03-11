
in float att_factor[MAX_LIGHTS];
in vec3 vt_Normal, light_dir[MAX_LIGHTS], eye_vec;
out vec4 out_Color;

void compute_light(light_t light, vec3 N, vec3 L, float att_factor) {
	out_Color += mat.emission + mat.ambient * ambient;
	float lambertTerm = dot(N, L);

	if (lambertTerm > 0) {
		out_Color += light.diffuse * mat.diffuse * lambertTerm * att_factor;
		
		vec3 E = normalize(eye_vec);
		vec3 R = reflect(-L, N);
		float spec_factor = pow( max(dot(R, E), 0.0), mat.shininess );
		out_Color += light.specular * mat.specular * spec_factor * att_factor;
	}
	
}

void phong(void)
{
	out_Color = vec4(0,0,0,0);
	vec3 N = normalize(vt_Normal);

	//for(int i = 0;i < lights; i++) {
	vec3 L = normalize(light_dir[0]);
	compute_light(light[0], N, L, att_factor[0]);
	L = normalize(light_dir[1]);
	compute_light(light[1], N, L, att_factor[1]);
		/*L = normalize(light_dir[0]);
		compute_light(light[0], N, L);*/
	//}
}
