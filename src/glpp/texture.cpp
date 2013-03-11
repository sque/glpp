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
#include "texture.hpp"
#include "exception.hpp"

namespace glpp{

	// Generate one texture
	texture::texture(const texture_type & type):
		m_tex_type(type){
		::glGenTextures(1, &m_gl_name);

		assert_no_glerror("glGenTextures failed. ");
	}

	texture::~texture() {
		if (glIsTexture(object_name()))
			glDeleteTextures(1, &m_gl_name);
	}


	void texture::set_base_level(GLint lvl) {
		set_parami(param_type::MIN_FILTER, lvl);
	}

	void texture::set_border_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
		GLfloat colors[4] = {b, g, r, a};
		set_paramfv(param_type::BORDER_COLOR, colors);
	}

	void texture::set_compare_func(compare_func cf) {
		set_parami(param_type::COMPARE_FUNC, GLPP_CAST_TO_SCALAR(GLint, cf));
	}

	void texture::set_compare_mode(compare_mode cm) {
		set_parami(param_type::COMPARE_MODE, GLPP_CAST_TO_SCALAR(GLint, cm));
	}

	void texture::set_lod_bias(GLfloat bias) {
		set_paramf(param_type::LOD_BIAS, bias);
	}

	void texture::set_min_filter(min_filter_type mf) {
		set_parami(param_type::MIN_FILTER, GLPP_CAST_TO_SCALAR(GLint, mf));
	}

	void texture::set_mag_filter(mag_filter_type mf) {
		set_parami(param_type::MAG_FILTER, GLPP_CAST_TO_SCALAR(GLint, mf));
	}

	void texture::set_min_lod(GLfloat lvl) {
		set_paramf(param_type::MIN_LOD, lvl);
	}

	void texture::set_max_lod(GLfloat lvl) {
		set_paramf(param_type::MIN_LOD, lvl);
	}

	void texture::set_max_level(GLint lvl) {
		set_parami(param_type::MAX_LEVEL, lvl);
	}

	void texture::set_swizzle(swizzle_type r, swizzle_type g, swizzle_type b, swizzle_type a) {
		GLint rgba[4] = { GLPP_CAST_TO_SCALAR(GLint, r), GLPP_CAST_TO_SCALAR(GLint, g), GLPP_CAST_TO_SCALAR(GLint, b), GLPP_CAST_TO_SCALAR(GLint, a)};
		set_paramiv(param_type::SWIZZLE_RGBA, rgba);
	}

	void texture::set_wrap_s(wrap_type ws) {
		set_parami(param_type::WRAP_S, GLPP_CAST_TO_SCALAR(GLint, ws));
	}

	void texture::set_wrap_t(wrap_type wt) {
		set_parami(param_type::WRAP_T, GLPP_CAST_TO_SCALAR(GLint, wt));
	}

	void texture::set_wrap_r(wrap_type wr) {
		set_parami(param_type::WRAP_R, GLPP_CAST_TO_SCALAR(GLint, wr));
	}


	void texture::get_border_color(GLfloat * rgba) const {
		get_paramfv(param_type::BORDER_COLOR, rgba);
	}

	void texture::get_border_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a) const {
		GLfloat rgba[4];
		get_border_color(rgba);
		r = rgba[0];
		g = rgba[1];
		b = rgba[2];
		a = rgba[3];
	}


	GLint texture::get_base_level() const {
		return get_parami(param_type::BASE_LEVEL);
	}


	GLint texture::get_max_level() const {
		return get_parami(param_type::MAX_LEVEL);
	}

	compare_mode texture::get_compare_mode() const {
		return GLPP_CAST_TO_SAFE_ENUM(compare_mode, get_parami(param_type::COMPARE_MODE));
	}

	compare_func texture::get_compare_func() const {
		return GLPP_CAST_TO_SAFE_ENUM(compare_func, get_parami(param_type::COMPARE_FUNC));
	}

	GLfloat texture::get_min_lod() const {
		return get_paramf(param_type::MIN_LOD);
	}

	GLfloat texture::get_max_lod() const {
		return get_paramf(param_type::MAX_LOD);
	}

	void texture::get_swizzle(swizzle_type & r, swizzle_type & g, swizzle_type & b, swizzle_type & a) const {
		GLint rgba[4];
		get_paramiv(param_type::SWIZZLE_RGBA, rgba);
		r = GLPP_CAST_TO_SAFE_ENUM(swizzle_type, rgba[0]);
		g = GLPP_CAST_TO_SAFE_ENUM(swizzle_type, rgba[1]);
		b = GLPP_CAST_TO_SAFE_ENUM(swizzle_type, rgba[2]);
		a = GLPP_CAST_TO_SAFE_ENUM(swizzle_type, rgba[3]);
	}

	wrap_type texture::get_wrap_r() const {
		return GLPP_CAST_TO_SAFE_ENUM(wrap_type, get_parami(param_type::WRAP_R));
	}

	wrap_type texture::get_wrap_s() const {
		return GLPP_CAST_TO_SAFE_ENUM(wrap_type, get_parami(param_type::WRAP_S));
	}

	wrap_type texture::get_wrap_t() const {
		return GLPP_CAST_TO_SAFE_ENUM(wrap_type, get_parami(param_type::WRAP_T));
	}

	bool texture::is_immutable_format() const {
		return static_cast<bool>(get_parami(param_type::IMMUTABLE_FORMAT));
	}

	void texture::define_data_2d(tex2d_update_target target,
			GLuint lvl,
			image_format internal_format,
			size_t width,
			size_t height,
			int border,
			pixel_format pix_form,
			tex_pixel_type pix_type,
			const void * pdata) {

		::glBindTexture(GLPP_CAST_TO_SCALAR(GLenum, type()), object_name());
		::glTexImage2D(GLPP_CAST_TO_SCALAR(GLenum, target), lvl, GLPP_CAST_TO_SCALAR(GLint, internal_format), width, height, border, GLPP_CAST_TO_SCALAR(GLenum, pix_form), GLPP_CAST_TO_SCALAR(GLenum, pix_type), pdata);
	}

	void texture::generate_mipmaps() {
		::glGenerateMipmap(GLPP_CAST_TO_SCALAR(GLenum, type()));
	}
}
