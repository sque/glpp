#version 420

uniform float pulse;

void noise(){
	gl_Position.x += mod(pulse, 0.0213);
	gl_Position.y += mod(pulse, 0.0452);
	gl_Position.z += mod(pulse, 0.0243);
}