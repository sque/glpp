#version 420

out vec4 out_Color;

in vec2 vt_TexCoords;

uniform sampler2D screenMap;


void pfx_oldconsole() {
	
	int wy = int(gl_FragCoord.y);
	if ((wy % 2) == 0 ) {
		out_Color = vec4(0,0,0,1);
	} else {
		float intensity = (out_Color.r + out_Color.g + out_Color.b )/3;
		out_Color = vec4(intensity * vec3(0,1,0),1);
		
		if ((wy % 3)  == 0)
			out_Color *= 0.4;
	}
}