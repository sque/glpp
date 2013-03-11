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
#include <iostream>
#include <stdio.h>

glpp::buffer * ptri_vbo;
glpp::vertex_array * ptri_vao;
glpp::program * pprog;
int frame_count = 0;

void disp_func() {
	frame_count ++;
	glClearColor(0.1, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	pprog->use();
	ptri_vao->draw(glpp::primitive_type::TRIANGLES, 0, 3);
	glutSwapBuffers();
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
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "unblocks.vert"));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "unblocks.frag"));
	pprog->build();

	// Get various uniform blocks
	glpp::shared_uniform_block_t p_ub_intA20_std140 = pprog->get_uniform_block("ub_intA20_std140");
	glpp::shared_uniform_block_t p_ub_intA20_packed = pprog->get_uniform_block("ub_intA20_packed");
	glpp::shared_uniform_block_t p_ub_str_intA20_std140 = pprog->get_uniform_block("ub_str_intA20_std140");
	glpp::shared_uniform_block_t p_ub_20int_std140 = pprog->get_uniform_block("ub_20int_std140");
	glpp::shared_uniform_block_t p_ub_strA10_3int_std140 = pprog->get_uniform_block("ub_strA10_3int_std140");
	std::cout << "Size of layout(std140) int[20] " << p_ub_intA20_std140->data_size() << std::endl;
	std::cout << "Size of layout(packed) int[20] " << p_ub_intA20_packed->data_size() << std::endl;
	std::cout << "Size of layout(std140) 20 x int; " << p_ub_20int_std140->data_size() << std::endl;
	std::cout << "Size of layout(std140) struct { int[20] }" << p_ub_str_intA20_std140->data_size() << std::endl;
	std::cout << "Size of layout(std140) struct[10] { int,int,int }" << p_ub_strA10_3int_std140->data_size() << std::endl;

	// Assure sizes as defined by spec
	assert(p_ub_intA20_std140->data_size() == 320);
	assert(p_ub_str_intA20_std140->data_size() == 320);
	assert(p_ub_intA20_std140->data_size() == 320);
	assert(p_ub_strA10_3int_std140->data_size() == 160);


	glpp::shared_uniform_t p_intA20_std140 = pprog->get_uniform("intA20_std140");
	std::cout << "offset(intA20_std140) " << p_intA20_std140->offset() << std::endl;
	std::cout << "Sizeof(intA20_std140) " << p_intA20_std140->size() << std::endl;
	std::cout << "Stride intA20_std140  " << p_intA20_std140->array_stride() << std::endl;
	std::cout << "Mat stride intA20_std140  " << p_intA20_std140->matrix_stride() << std::endl;
	std::cout << "is_row_major intA20_std140  " << p_intA20_std140->is_row_major() << std::endl;
	std::cout << "Type of intA20_std140  0x" << std::hex << GLPP_CAST_TO_SCALAR(GLenum, p_intA20_std140->type()) << std::dec << std::endl;


	glpp::shared_uniform_t p_m1 = pprog->get_uniform("m1");
	glpp::shared_uniform_t p_m2 = pprog->get_uniform("m2");
	std::cout << "offset(m1), sizeof(m1) " << p_m1->offset() << ", " << p_m1->size() << std::endl;
	std::cout << "offset(m2), sizeof(m2) " << p_m2->offset() << ", " << p_m2->size() << std::endl;
	std::cout << "blockof(m2) " << p_m2->owner_block()->object_name() << ", " <<  p_m2->owner_block()->block_name() << std::endl;
	std::cout << "blockof(intA20_std140) " << p_intA20_std140->owner_block()->object_name()
		<< ", " <<  p_intA20_std140->owner_block()->block_name()
		<< std::endl;

}

void show_fps(int data) {
	static int last_count = 0;
	float fps = (frame_count - last_count)/0.500;
	printf("FPS: %f\n", fps);
	last_count = frame_count;
	glutTimerFunc(500, show_fps, 1);
}

void idle_func() {
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
	glutIdleFunc(idle_func);

	GLuint err;
	if ((err = glewInit()) != GLEW_OK) {
		fprintf(stderr, "Cannot initialize GLEW. %s\n", glewGetErrorString(err));
		return -1;
	}
	load_triangle();

	glpp::context::create();

	glutMainLoop();
	return 0;
}


