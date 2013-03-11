#version 330

in vec4 ex_Color;
in float ex_Test;
out vec4 out_Color;
uniform float Time;

void main(void)
{
	//out_Color = vec4(sin(0.5 - ex_Test),sin(1 - ex_Test),sin(ex_Test),0);
	out_Color = vec4(sin(0.5 - ex_Test + Time),sin(1 - ex_Test +Time),sin(ex_Test +Time),0);
	//out_Color = vec4(1,1,1,1);
}
