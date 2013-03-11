#version 420

out vec4 out_Color;

void interleave(void) {
	int wy = int(gl_FragCoord.y);
	if (wy % 2 == 0){
		out_Color = vec4(0,0,0,0);
	}
}