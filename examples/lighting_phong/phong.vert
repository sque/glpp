
layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 N;

out vec3 vt_Normal, light_dir[MAX_LIGHTS], eye_vec;
out float att_factor[MAX_LIGHTS];

uniform mat4 ModelViewMatrix;

void phong(void) {
	
	eye_vec = - vec4(ModelViewMatrix * in_Position).xyz;
	
	
	light_dir[0] = light[0].position - in_Position.xyz;
	att_factor[0] = get_attenuation(light[0], in_Position.xyz);
	light_dir[1] = light[1].position - in_Position.xyz;	
	att_factor[1] = get_attenuation(light[1], in_Position.xyz);
	vt_Normal = normalize(vec4(transpose(inverse(ModelViewMatrix)) * N).xyz);
}

