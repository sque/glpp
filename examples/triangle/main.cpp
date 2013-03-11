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

glpp::buffer * ptri_vbo;
glpp::vertex_array * ptri_vao;
glpp::program * pprog;

int frame_count = 0;

void setup_scene() {

	// Vertex information
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

	// Load triangle vertices data in a buffer
	ptri_vbo = new glpp::buffer(glpp::buffer_type::ARRAY);
	ptri_vbo->define_data(sizeof(data), data, glpp::buffer_usage_pattern::STATIC_DRAW);

	// Construct the vertex array object of the triangle
	ptri_vao = new glpp::vertex_array();
	// Attribute 0 carries the vertex position
	ptri_vao->attrib(0)->set_pointerf(*ptri_vbo, 3, glpp::attribf_data_type::FLOAT, 28, 0);
	ptri_vao->attrib(0)->enable();
	// Attribute 1 carries the vertex color
	ptri_vao->attrib(1)->set_pointerf(*ptri_vbo, 3, glpp::attribf_data_type::FLOAT, 28, sizeof(GLfloat)*3);
	ptri_vao->attrib(1)->enable();

	// Load shaders
	pprog = new glpp::program();
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, "triangle.vert"));
	pprog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, "triangle.frag"));
	pprog->build();
	pprog->use();
}

// Display FPS
void show_fps(int data) {
	static int last_count = 0;

	float fps = (frame_count - last_count)/0.500;
	last_count = frame_count;

	printf("FPS: %f\n", fps);

	// Re-register for the next time
	glutTimerFunc(500, show_fps, 1);
}

void idle_func() {
	::glutPostRedisplay();
}

void draw_window_func() {

	frame_count ++;

	// Clear buffers
	glClearColor(0.1, 0.1, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw 3 vertices starting at position 0
	ptri_vao->draw(0, 3);
	glutSwapBuffers();
}

int main(int argv, char ** argc) {

	// Initialize GLUT
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("GL++ Example: Triangle");
	glutDisplayFunc(draw_window_func);
	glutTimerFunc(500, show_fps, 1);
	glutIdleFunc(idle_func);

	// Initialize GLEW and GLPP
	GLuint err;
	if ((err = glewInit()) != GLEW_OK) {
		fprintf(stderr, "Cannot initialize GLEW. %s\n", glewGetErrorString(err));
		return -1;
	}
	glpp::context::create();

	// Setup scene
	setup_scene();

	// Render loop
	glutMainLoop();

	return 0;
}
