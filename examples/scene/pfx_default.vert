#version 420

layout(location=0) in vec2 in_Position;

out vec2 vt_TexCoords;

void pfx_default(){
	gl_Position = vec4(in_Position, 0, 1);
	vt_TexCoords = (in_Position.xy + 1.0) / 2.0;
}