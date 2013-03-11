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
#include <assert.h>
#include "../common/commons.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <iostream>

#define RTT_WIDTH 300
#define RTT_HEIGHT 300

glpp::buffer * ptri_vbo;
glpp::vertex_array * ptri_vao;
glpp::program * pprog;
glpp::program * pplaneprog;
glpp::frame_buffer * pfb;
geometry * pobj;
glpp::shared_texture_t prtt;
glpp::shared_render_buffer_t rnbdep;

int frame_count = 0;

void disp_func() {
	frame_count ++;

	pfb->bind();
	glViewport(0, 0, RTT_WIDTH, RTT_HEIGHT);
	glClearColor(0.1, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pprog->use();
	ptri_vao->draw(0, 3);
	glpp::assert_no_glerror("Error drawing offscreen");

	glpp::frame_buffer::window_default().bind();
	glViewport(0, 0, 480, 640);
	glClearColor(0.4, 0.4, 0.4, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	pplaneprog->use();
	pobj->draw();


	glutSwapBuffers();
}

void load_models() {
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

	// Triangle shader
	pprog = new glpp::program();
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "triangle.vert"));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "triangle.frag"));
	pprog->build();

	// Plane shader
	pplaneprog = new glpp::program();
	pplaneprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "rtt_persp.vert"));
	pplaneprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "rtt_persp.frag"));
	pplaneprog->build();
	std::cout << " RTT " << prtt->object_name() << std::endl;
	glpp::assert_no_glerror("Trying to setup colormap");

	glm::mat4 Proj = glm::perspective(45.0f, 1.3f, 0.1f, 20.0f);
	glm::mat4 ViewModel = glm::mat4(1.0f);
	ViewModel = glm::translate(ViewModel, glm::vec3(0.0f, 0.0f, -2.0f));
	ViewModel = glm::rotate(ViewModel, -55.0f, glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f)));
	glm::mat4 ProjModView = Proj * ViewModel;;
	pplaneprog->get_global_uniform("ProjModView")->setmat4f(glm::value_ptr(ProjModView), false, 1);

	pobj = new plane(glm::vec3(.0f, 1.0f, .0f), glm::vec3(1.0f, .0f, .0f), 1, 1);
	pobj->create_globjects();
}

void show_fps(int data) {
	static int last_count = 0;
	float fps = (frame_count - last_count)/0.500;
	double frame_render = 1.0f/fps;
	printf("FPS: %-4f, frame render time: %-4f \n", fps, frame_render);
	last_count = frame_count;
	glutTimerFunc(500, show_fps, 1);
}

void idle_func() {
	::glutPostRedisplay();
}

int main(int argv, char ** argc) {
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(480, 640);
	glutCreateWindow("GL++ Test: RTT");
	glutDisplayFunc(disp_func);
	glutTimerFunc(500, show_fps, 1);
	glutIdleFunc(idle_func);

	GLuint err;
	if ((err = glewInit()) != GLEW_OK) {
		fprintf(stderr, "Cannot initialize GLEW. %s\n", glewGetErrorString(err));
		return -1;
	}

	glpp::context::create();
	glpp::current_ctx().depth_test().enable();

	pfb = new glpp::frame_buffer(glpp::frame_buffer_target::DRAW);
	prtt  = glpp::shared_texture_t(new glpp::texture(glpp::texture_type::TEX_2D));
	std::array<float, 4 * RTT_WIDTH * RTT_HEIGHT> img_storage;
	img_storage.fill(0);
	prtt->define_data_2d(
			glpp::tex2d_update_target::TEX_2D,
			0,
			glpp::image_format::RGBA,
			RTT_WIDTH,
			RTT_HEIGHT,
			0,
			glpp::pixel_format::RGBA,
			glpp::tex_pixel_type::FLOAT,
			&img_storage[0]);
	prtt->set_min_filter(glpp::min_filter_type::LINEAR);
	prtt->set_mag_filter(glpp::mag_filter_type::LINEAR);
	prtt->set_wrap_s(glpp::wrap_type::MIRRORED_REPEAT);
	prtt->set_wrap_t(glpp::wrap_type::MIRRORED_REPEAT);

	glpp::shared_render_buffer_t rnbdep = glpp::shared_render_buffer_t(new glpp::render_buffer());
	rnbdep->define_storage(glpp::image_rendable_format::DEPTH_COMPONENT, RTT_WIDTH, RTT_HEIGHT);
	pfb->point(glpp::fbo_point::COLOR0)->attach(prtt, 0);
	pfb->point(glpp::fbo_point::DEPTH)->attach(rnbdep);

	assert(pfb->is_complete());
	glpp::frame_buffer::window_default().bind();
	load_models();


	glutMainLoop();
	return 0;
}
