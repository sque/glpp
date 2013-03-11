#version 420

in vec4 dbg_Color;
out vec4 out_Color;

void debug(void) {
	out_Color = dbg_Color;
}