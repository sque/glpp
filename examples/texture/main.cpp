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
#include <glm/gtx/rotate_vector.hpp>
#include <sys/timeb.h>
#include <iostream>
#include <boost/format.hpp>
#include "../common/commons.hpp"


bool paused = false;
int frame_count = 0;


scene * pscene;
mouse_drag left_btn;

void disp_func() {
	frame_count ++;

	glClearColor(0.1, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	pscene->draw();

	glutSwapBuffers();
}

void load_models() {

	geometry * pobj;

	pobj = pscene->attach_object("light0", new sphere(0.3, 5, 5));
	pobj->material.emission = glm::vec4(1,1,1,1);
	pobj = pscene->attach_object("light1", new sphere(0.3, 5, 5));
	pobj->material = pscene->get_object("light0").material;


	pobj = pscene->attach_object("sphere", new sphere(1, 100, 100));
	pobj->position.x = 6;


	pobj = pscene->attach_object("monkey", new geometry("models/monkey_painted.dae"));
	pobj->material.diffuse = glm::vec4(0,0,0,1);
	pobj->load_texture("models/monkey.png");

	pobj = pscene->attach_object("cube", new cube(1));
	pobj->position = glm::vec3(5, 3, 0);

	pobj = pscene->attach_object("plane", new plane(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), 30, 30));
	pobj->load_texture("models/wall_normals.jpg");
	pobj->position = glm::vec3(0, -1, 0);

	pobj = pscene->attach_object("plane2", new plane(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), 30, 30));
	pobj->load_texture("models/wall_normals.jpg");
	pobj->position = glm::vec3(-15, 0, 0);


	//pobj = pscene->attach_object("skybox", new skybox(10, "../models/enviroment_storm.jpg", { "skybox.vert"}, {"skybox.frag"}));

	pscene->create_globjects();
}

void load_textures() {
	glpp::current_ctx().texture_unit(0).activate();
	glpp::texture * pstenv = new glpp::texture(glpp::texture_type::TEX_CUBEMAP);
	load_texturecube_from_file(pstenv, "models/enviroment_storm.jpg", true);

	glpp::assert_no_glerror("GL_TEXTURE_2D failed.");
}

void load_scene() {


	pscene = new scene();

	pscene->attach_light(*new light());
	pscene->get_light(0).position = glm::vec3(0, 1, 10);
	pscene->get_light(0).diffuse = glm::vec4(.7, .7, .7, 1);
	pscene->get_light(0).specular = glm::vec4(1, 1, 1, 1);
	pscene->get_light(0).quad_att_factor = 0.002;

	pscene->attach_light(*new light());
	pscene->get_light(1).position = glm::vec3(0, 1, -5);
	pscene->get_light(1).diffuse = glm::vec4(.8, .2, .2, 1);
	pscene->get_light(1).specular = glm::vec4(1, .2, .2, 1);

	load_textures();
}

void load_shaders(){
	pscene->get_object("monkey").set_effect(new effect({"position", "normals", "phong", "reflection"}, "effects"))->build();
	pscene->get_object("sphere").set_effect(new effect({"position", "wave", "normals","phong"}, "effects"))->build();
	pscene->get_object("cube").set_effect(new effect({"position", "normals","phong"}, "effects"))->build();
	pscene->get_object("plane").set_effect(new effect({"position", "normals", "bump", "phong"}, "effects"))->build();
	pscene->get_object("plane2").set_effect(&pscene->get_object("plane").get_effect());
	pscene->get_object("light0").set_effect(new effect({"position", "phong"}, "effects"))->build();
	pscene->get_object("light1").set_effect(&pscene->get_object("light0").get_effect());
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
	pscene->get_light(0).position = glm::rotate(pscene->get_light(0).position, -.2f, glm::vec3(0,1,0));
	pscene->get_object("light0").position = pscene->get_light(0).position;
	pscene->get_light(1).position = glm::rotate(pscene->get_light(1).position, .3f, glm::vec3(0,1,0));
	pscene->get_object("light1").position = pscene->get_light(1).position;

	glm::vec3 & pos = pscene->get_object("sphere").position;
	pos = glm::rotate(pos, .3f, glm::vec3(0,1,0));
}

void idle_func() {
	rand();
	::glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON ){
		if (state == GLUT_DOWN)
			left_btn.start_dragging(x, y);
		else
			left_btn.stop_dragging();
	}

	if ((button == 3) && (state == GLUT_UP)) {
		pscene->get_camera().zoom_in(0.5);
	} else if ((button == 4) && (state == GLUT_UP)){
		pscene->get_camera().zoom_out(0.5);
	}
}

void mouse_motion_func(int x, int y) {
	if (left_btn.is_dragging()) {
		glm::vec2 drag = left_btn.get_drag(x, y);
		pscene->get_camera().yaw_world_center(drag.x);
		pscene->get_camera().pitch_world_center(drag.y);
	}
}

void reshape_func(int width, int height) {
	pscene->get_camera().aspect((float)width/(float)height);
}

void keyb_func(unsigned char key, int x, int y) {
	switch(key){
	case ' ':
		paused = !paused;
		break;
	}
}

int main(int argv, char ** argc) {
	try {
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

		std::cout << "Total texture units " << glpp::current_ctx().capabilities().total_texture_units() << std::endl;
		std::cout << "Maximum texture size " << glpp::current_ctx().capabilities().max_texture_size() << std::endl;


		load_scene();
		load_models();
		load_shaders();
		load_textures();
		glpp::assert_no_glerror("Initialized engine.");

		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_CULL_FACE);
		glutMainLoop();
	} catch(std::exception & e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
