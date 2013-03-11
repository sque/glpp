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
#include <sys/timeb.h>


glpp::buffer * ptri_vbo;
glpp::vertex_array * ptri_vao;

glpp::program * pprog;
glm::vec2 obj_rot(30,0);
glm::vec3 obj_scale(1);
float obj_scale_factor = 0.02;
int frame_count = 0;

void disp_func() {
	frame_count ++;
	glClearColor(0.1, 0.1, 0.2, 1);
	//glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pprog->use();
	struct timeb tp;
	ftime(&tp);
	float pulse = (double)tp.millitm/1000.0f;
	if (tp.time % 2) {
		pulse = 1.0 - pulse;
	}
	pprog->get_global_uniform("Time")->set1f(pulse);
	ptri_vao->draw_instances(0, 3, 10000);
	glutSwapBuffers();
}

void init_prespective (){
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
	glm::mat4 ViewTranslate = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(10.0f, -3.0f, -10.0f));

	glm::mat4 View = ViewTranslate;
	/*glm::mat4 ViewRotateX = glm::rotate(
			ViewTranslate,
			obj_rot.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 View = glm::rotate(
			ViewRotateX,
			obj_rot.x, glm::vec3(0.0f, 1.0f, 0.0f));*/
	glm::mat4 Model = glm::scale(
			glm::mat4(1.0f),
			obj_scale);
	Model = glm::rotate(
			Model,
			obj_rot.x, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 MVP = Projection * View * Model;

	pprog->use();
	::glUniformMatrix4fv(pprog->get_global_uniform("ProjectionMatrix")->object_name(),
			1, GL_FALSE, glm::value_ptr(MVP));
}

void load_triangle() {
	struct vector{
		GLfloat x;
		GLfloat y;
		GLfloat z;
		struct {
			GLfloat r;
			GLfloat g;
			GLfloat b;
			GLfloat a;
		} color;
	};
	/* Vertices of a triangle (counter-clockwise winding) */
	vector data[3] = {
			{ 0.0, 1.0, 0.0, {1, 0, 0} },
			{ -1.0, -1.0, 0.0, {0, 1, 0} },
			{ 1.0, -1.0, 0.0, {0, 0, 1} }
	};
	ptri_vbo = new glpp::buffer(glpp::buffer_type::ARRAY);
	ptri_vbo->define_data(sizeof(data), data, glpp::buffer_usage_pattern::STATIC_DRAW);

	ptri_vao = new glpp::vertex_array();
	ptri_vao->attrib(0)->set_pointerf(*ptri_vbo, 3, glpp::attribf_data_type::FLOAT, 28, 0);
	ptri_vao->attrib(0)->enable();
	ptri_vao->attrib(1)->set_pointerf(*ptri_vbo, 3, glpp::attribf_data_type::FLOAT, 28, sizeof(GLfloat)*3);
	ptri_vao->attrib(1)->enable();

	// Load shaders
	pprog = new glpp::program();
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "instances.vert"));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "instances.frag"));
	pprog->build();
}

void show_fps(int data) {
	static int last_count = 0;
	float fps = (frame_count - last_count)/0.500;
	printf("FPS: %f\n", fps);
	last_count = frame_count;
	glutTimerFunc(500, show_fps, 1);
}

void transform_func(int data) {
return;
	obj_rot.x += 0.5;
	//obj_rot.y += 1;
	/*obj_scale += obj_scale_factor;
	if ((obj_scale.x < 0.2) || (obj_scale.x > 2)) {
		obj_scale_factor = -obj_scale_factor;
	}*/

	init_prespective();
	glutTimerFunc(10, transform_func, 1);
}

void idle_func() {
	rand();
	::glutPostRedisplay();
}

int main(int argv, char ** argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//glutInitContextVersion(3, 3);
	//glutInitContextFlags(GLUT_COMPATIBILITY_PROFILE);
	glutCreateWindow("OGL Test: Triangle");
	glutDisplayFunc(disp_func);
	glutTimerFunc(500, show_fps, 1);
	glutTimerFunc(10, transform_func, 1);
	glutIdleFunc(idle_func);
	glpp::context::create();
	glpp::current_ctx().depth_test().enable();

	GLuint err;
	if ((err = glewInit()) != GLEW_OK) {
		fprintf(stderr, "Cannot initialize GLEW. %s\n", glewGetErrorString(err));
		return -1;
	}
	load_triangle();
	init_prespective();

	glutMainLoop();
	return 0;
}
