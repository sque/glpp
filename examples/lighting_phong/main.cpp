/**
 * Copyright (c) 2012 Konstantinos Paliouras <squarious _ gmail _dot com>.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <glpp/glpp.hpp>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <sys/timeb.h>
#include <iostream>
#include <boost/format.hpp>
#include "../common/commons.hpp"


bool paused = false;
glpp::program * pprog;
glm::vec2 obj_rot(30,0);
glm::vec3 obj_scale(1);
glm::vec3 camera_pos(0, 0, 5);
float obj_scale_factor = 0.02;
int frame_count = 0;
std::vector<light> lights;

geometry * pmonkey;
geometry * psphere;

void disp_func() {
	frame_count ++;

	glClearColor(0.1, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT));

	pprog->use();
	//pprog->get_global_uniform("lights")->set1i(lights.size());
	lights[0].set_uniforms(pprog, "light[0].");
	lights[1].set_uniforms(pprog, "light[1].");

	pprog->get_global_uniform("ambient")->set4f(0.1,0.1,0.1,1);
	pprog->get_global_uniform("mat.emission")->set4f(0, 0 ,0 , 1);
	pprog->get_global_uniform("mat.specular")->set4f(1,1,1,1);
	pprog->get_global_uniform("mat.shininess")->set1f(6);
	pprog->get_global_uniform("mat.ambient")->set4f(0.2, 0.2, 0.2, 1);
	pprog->get_global_uniform("mat.diffuse")->set4f(0.5, 0.5, 0.5, 1);
	pprog->get_global_uniform("pulse")->set1f(clock() % 1123123);

	pmonkey->draw();

	glViewport(glutGet(GLUT_WINDOW_WIDTH)/2, 0, glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT));
	psphere->draw();

	glFlush();
	glutSwapBuffers();
}

void update_prespective (){
	float aspect = glutGet(GLUT_WINDOW_WIDTH)/2;
	aspect /= glutGet(GLUT_WINDOW_HEIGHT);
	glm::mat4 Projection = glm::perspective(45.0f, aspect, 0.1f, 1000.f);
	glm::mat4 ViewTranslate = glm::translate(
		glm::mat4(1.0f),
		-camera_pos);

	glm::mat4 View = ViewTranslate;
	glm::mat4 Model = glm::scale(
			glm::mat4(1.0f),
			obj_scale);
	Model = glm::rotate(
			Model,
			obj_rot.y, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(
			Model,
			obj_rot.x, glm::vec3(0.0f, 1.0f, 0.0f));


	glm::mat4 MV = View * Model;

	pprog->use();
	pprog->get_global_uniform("ModelViewMatrix")->setmat4f(glm::value_ptr(MV), false);
	pprog->get_global_uniform("ProjectionMatrix")->setmat4f(glm::value_ptr(Projection), false);
}

void load_models() {
	pmonkey = new geometry("models/monkey_painted.dae");
	pmonkey->create_globjects();

	psphere = new sphere(1, 100, 100);
	psphere->create_globjects();

	//psphere = new cube(1);
	//psphere->create_globjects();
}

void load_scene() {

	lights.resize(2);

	lights[0].position = glm::vec3(0, 10, 10);
	lights[0].diffuse = glm::vec4(.0, .5, .0, 1);
	lights[0].specular = glm::vec4(.5, 1, .5, 1);

	lights[1].position = glm::vec3(0, 10, -10);
	lights[1].diffuse = glm::vec4(.4, 0, 0, 1);
	lights[1].specular = glm::vec4(1,0.5,0.5,1);
}

void load_shaders(){
	pprog = new glpp::program();

	// Load shaders
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {"effects/position.vert"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {"effects/phong.hsh", "effects/phong.vert"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {"effects/noise.vert"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {"effects/main.vert"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {"effects/wave.vert"}));

	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, {"effects/phong.hsh", "effects/phong.frag"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, {"effects/interleaved.frag"}));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, {"effects/main.frag"}));
	pprog->build();

	std::cout << pprog->info_log() << std::endl;

}

void show_fps(int data) {
	static int last_count = 0;
	float fps = (frame_count - last_count)/0.500;
	printf("FPS: %f\n", fps);
	last_count = frame_count;
	glutTimerFunc(500, show_fps, 1);
}

void pulse_func_10(int data) {
	glutTimerFunc(10, pulse_func_10, 1);
	if(paused)
		return;
	lights[0].position = glm::rotate(lights[0].position, -.2f, glm::vec3(0,1,0));
	//std::cout << boost::format("%1% %2% %3%")
	//% lights[0].position.x % lights[0].position.y % lights[0].position.z << std::endl;
	lights[1].position = glm::rotate(lights[1].position, .2f, glm::vec3(0,1,0));


}

void idle_func() {
	rand();
	::glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
	if ((button == 3) && (state == GLUT_UP)) {
			camera_pos.z -= 0.2;
			// Zoom in
	} else if ((button == 4) && (state == GLUT_UP)){
			camera_pos.z += 0.2;
		// Zoom out
	}
	update_prespective();
}
void mouse_motion_func(int x, int y) {
	static int previous_x = -1;
	static int previous_y = -1;

	printf("mouse func: (x,y)=(%d,%d)\n", x, y);
	if (previous_x != -1) {
		obj_rot.x += x - previous_x;
	}
	if (previous_y != -1) {
		obj_rot.y += y - previous_y;
	}

	update_prespective();
	previous_x = x;
	previous_y = y;
}

void reshape_func(int width, int height) {
	update_prespective();
}

void keyb_func(unsigned char key, int x, int y) {
	switch(key){
	case ' ':
		paused = !paused;
		break;
	}
}
int main(int argv, char ** argc) {

		glutInit(&argv, argc);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		//glutInitContextVersion(3, 3);
		//glutInitContextFlags(GLUT_COMPATIBILITY_PROFILE);
		glutCreateWindow("OGL Test: Triangle");
		glutDisplayFunc(disp_func);
		glutReshapeFunc(reshape_func);
		glutTimerFunc(500, show_fps, 1);
		glutTimerFunc(10, pulse_func_10, 1);
		glutIdleFunc(idle_func);
		glutMouseFunc(mouse_func);
		glutMotionFunc(mouse_motion_func);
		glutKeyboardFunc(keyb_func);
		glpp::context::create();
		glpp::current_ctx().depth_test().enable();

		GLuint err;
		if ((err = glewInit()) != GLEW_OK) {
			fprintf(stderr, "Cannot initialize GLEW. %s\n", glewGetErrorString(err));
			return -1;
		}

		load_models();
		load_shaders();
		load_scene();

		std::cout << "Total tex units " << glpp::current_ctx().capabilities().total_texture_units() << std::endl;

		update_prespective ();
		glEnable(GL_CULL_FACE);
		glutMainLoop();


	return 0;
}
