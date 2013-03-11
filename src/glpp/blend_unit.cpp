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
#include "blend_unit.hpp"
#include "context.hpp"

namespace glpp {

	blend_unit::blend_unit(context & ctx)
		:m_ctx(ctx){
	}

	void blend_unit::enable() {
		::glEnable(GL_BLEND);
	}

	void blend_unit::disable() {
		::glDisable(GL_BLEND);
	}

	bool blend_unit::is_enabled() {
		return m_ctx.get_param_bool(context_param_type::BLEND);
	}

	void blend_unit::set_write_mask(bool red, bool green, bool blue, bool alpha) {
		::glColorMask(red, green, blue, alpha);
	}

	void blend_unit::set_buffer_write_mask(GLuint buffer_index, bool red, bool green, bool blue, bool alpha) {
		::glColorMaski(buffer_index, red, green, blue, alpha);
	}

	void blend_unit::get_write_mask(bool & red, bool & green, bool & blue, bool & alpha) {
		GLboolean rgba[4];
		::glGetBooleanv(GL_COLOR_WRITEMASK, rgba);
		red = rgba[0];
		green = rgba[1];
		blue = rgba[2];
		alpha = rgba[3];
	}

	void blend_unit::set_func(blend_factor sfactor, blend_factor dfactor) {
		::glBlendFunc(GLPP_CAST_TO_SCALAR(GLenum, sfactor), GLPP_CAST_TO_SCALAR(GLenum, dfactor));
	}

	void blend_unit::set_buffer_func(GLuint buffer_index, blend_factor sfactor, blend_factor dfactor) {
		::glBlendFunci(buffer_index, GLPP_CAST_TO_SCALAR(GLenum, sfactor), GLPP_CAST_TO_SCALAR(GLenum, dfactor));
	}

	void blend_unit::set_func_components(blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha) {
		::glBlendFuncSeparate(GLPP_CAST_TO_SCALAR(GLenum, srgb), GLPP_CAST_TO_SCALAR(GLenum, drgb), GLPP_CAST_TO_SCALAR(GLenum, salpha), GLPP_CAST_TO_SCALAR(GLenum, dalpha));
	}

	void blend_unit::set_buffer_func_components(GLuint buffer_index, blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha) {
		::glBlendFuncSeparatei(buffer_index, GLPP_CAST_TO_SCALAR(GLenum, srgb), GLPP_CAST_TO_SCALAR(GLenum, drgb), GLPP_CAST_TO_SCALAR(GLenum, salpha), GLPP_CAST_TO_SCALAR(GLenum, dalpha));
	}


	void blend_unit::get_func_rgb(blend_factor & sfactor, blend_factor & dfactor) {
		sfactor = GLPP_CAST_TO_SAFE_ENUM(blend_factor, m_ctx.get_param_int(context_param_type::BLEND_SRC_RGB));
		dfactor = GLPP_CAST_TO_SAFE_ENUM(blend_factor, m_ctx.get_param_int(context_param_type::BLEND_DST_RGB));
	}

	void blend_unit::get_func_alpha(blend_factor & sfactor, blend_factor & dfactor) {
		sfactor = GLPP_CAST_TO_SAFE_ENUM(blend_factor, m_ctx.get_param_int(context_param_type::BLEND_SRC_ALPHA));
		dfactor = GLPP_CAST_TO_SAFE_ENUM(blend_factor, m_ctx.get_param_int(context_param_type::BLEND_DST_ALPHA));
	}


	void blend_unit::set_const_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		::glBlendColor(r, g, b, a);
	}

	void blend_unit::get_const_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a) {
		std::vector<float> rgba = m_ctx.get_param_floatv(context_param_type::BLEND_COLOR, 4);
		r = rgba[0];
		g = rgba[1];
		b = rgba[2];
		a = rgba[3];
	}

	void blend_unit::set_equation(blend_equation mode) {
		::glBlendEquation(GLPP_CAST_TO_SCALAR(GLenum, mode));
	}

	void blend_unit::set_buffer_equation(GLuint buffer_index, blend_equation mode) {
		::glBlendEquationi(buffer_index, GLPP_CAST_TO_SCALAR(GLenum, mode));
	}

	blend_equation blend_unit::get_equation_rgb() {

		return GLPP_CAST_TO_SAFE_ENUM(blend_equation, m_ctx.get_param_int(context_param_type::BLEND_EQUATION_RGB));
	}

	blend_equation blend_unit::get_equation_alpha() {
		return GLPP_CAST_TO_SAFE_ENUM(blend_equation, m_ctx.get_param_int(context_param_type::BLEND_EQUATION_ALPHA));
	}

}
