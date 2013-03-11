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
#include "post_effects.hpp"


post_effects::post_effects(int width, int height, glm::vec4 clear_color) :
	m_width(width),
	m_height(height),
	mp_texture(),
	mp_fbo_off(nullptr),
	mp_effects(nullptr),
	mp_depth_renderbuffer(nullptr),
	m_clear_color(clear_color){

	glpp::current_ctx().texture_unit(15).activate();
	mp_texture = glpp::shared_texture_t(new glpp::texture(glpp::texture_type::TEX_2D));
	mp_texture->define_data_2d(
			glpp::tex2d_update_target::TEX_2D,
			0,
			glpp::image_format::RGBA,
			width,
			height,
			0,
			glpp::pixel_format::RGBA,
			glpp::tex_pixel_type::UNSIGNED_BYTE,
			nullptr);
	mp_texture->set_min_filter(glpp::min_filter_type::LINEAR);
	mp_texture->set_mag_filter(glpp::mag_filter_type::LINEAR);
	mp_texture->set_wrap_s(glpp::wrap_type::CLAMP_TO_EDGE);
	mp_texture->set_wrap_t(glpp::wrap_type::CLAMP_TO_EDGE);

	mp_depth_renderbuffer = glpp::shared_render_buffer_t(new glpp::render_buffer());
	mp_depth_renderbuffer->define_storage(glpp::image_rendable_format::DEPTH_COMPONENT, width, height, 0);

	mp_fbo_off = new glpp::frame_buffer(glpp::frame_buffer_target::DRAW);
	mp_fbo_off->point(glpp::fbo_point::COLOR0)->attach(mp_texture, 0);
	mp_fbo_off->point(glpp::fbo_point::DEPTH)->attach(mp_depth_renderbuffer);
	if (!mp_fbo_off->is_complete()) {
		glpp::assert_no_glerror("FBO is not complete!");
	}

	// Texture vao;
	 GLfloat fbo_vertices[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		 1,  1,
	};
	mp_tex_vbo = new glpp::buffer (glpp::buffer_type::ARRAY);
	mp_tex_vbo->define_data(sizeof(GLfloat)*8, fbo_vertices, glpp::buffer_usage_pattern::STATIC_DRAW);
	mp_tex_vao = new glpp::vertex_array();
	mp_tex_vao->attrib(0)->set_pointerf(*mp_tex_vbo, 2, glpp::attribf_data_type::FLOAT, 0, 0);
	mp_tex_vao->attrib(0)->enable();

	glpp::current_ctx().texture_unit(15).bind_texture(*mp_texture);
}

void post_effects::reshape(int width, int height) {
	m_width = width;
	m_height = height;
	glpp::current_ctx().texture_unit(15).activate();
	mp_texture->define_data_2d(
		glpp::tex2d_update_target::TEX_2D,
		0,
		glpp::image_format::RGBA,
		width,
		height,
		0,
		glpp::pixel_format::RGBA,
		glpp::tex_pixel_type::UNSIGNED_BYTE,
		nullptr);
	mp_depth_renderbuffer->define_storage(glpp::image_rendable_format::DEPTH_COMPONENT, width, height, 0);

	glpp::assert_no_glerror("Reshaped finished with problems!");
}

void post_effects::draw() {

	if (mp_effects) {
		mp_effects->get_program().use();
		//mp_effects->get_program().get_uniform("screenMap").set1i(15);
		//mp_effects->get_program().get_uniform("width").set1i(m_width);
		//mp_effects->get_program().get_uniform("height").set1i(m_height);
		glpp::assert_no_glerror("Cannot set uniform");
	}

	glpp::frame_buffer::window_default().bind();
	glpp::current_ctx().depth_test().disable();
	glClearColor(m_clear_color.r, m_clear_color.g, m_clear_color.b, m_clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_width, m_height);
	mp_tex_vao->draw(0, 4);
	glpp::current_ctx().depth_test().enable();
}
