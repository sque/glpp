#version 420

void phong(void);
void interleave(void);
void reflection(void);

out vec4 out_Color;
void main(void){
	out_Color = vec4(0,0,0,1);
	phong();
	reflection();
}