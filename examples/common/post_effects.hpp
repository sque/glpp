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

#ifndef POST_EFFECTS_HPP_
#define POST_EFFECTS_HPP_

#include "internal.hpp"
#include "effect.hpp"

//! Render post effects
class post_effects {
public:

	post_effects(int width, int height, glm::vec4 clear_color);

	void bindAndClear() {
		mp_fbo_off->bind();
		::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void draw();

	inline int width() {
		return m_width;
	}

	inline int height() {
		return m_height;
	}

	effect * set_effects(effect * pfx) {
		mp_effects = pfx;
		mp_effects->build();
		mp_effects->get_program().get_global_uniform("screenMap")->set1i(15);
		return mp_effects;
	}

	effect *  get_effects() {
		return mp_effects;
	}

	void reshape(int width, int height);

protected:

	int m_width;

	int m_height;

	glpp::shared_texture_t mp_texture;

	glpp::frame_buffer * mp_fbo_off;

	effect * mp_effects;;

	glpp::shared_render_buffer_t mp_depth_renderbuffer;

	glpp::vertex_array * mp_tex_vao;

	glpp::buffer  * mp_tex_vbo;

	glm::vec4 m_clear_color;
};


#endif
