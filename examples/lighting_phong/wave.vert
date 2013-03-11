#version 420

uniform float pulse;

void wave(void){

	gl_Position.x += sin(pulse*gl_Position.y)*0.01;
}
