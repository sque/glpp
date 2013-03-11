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
#include "frame_buffer.hpp"

namespace glpp{


	frame_buffer_attachment_point::frame_buffer_attachment_point(const frame_buffer * pfbo, fbo_point point) :
		mp_fbo(pfbo),
		m_point(point){

	}

	void frame_buffer_attachment_point::attach(shared_texture_t & ptex, int level) {
		mp_fbo->bind();
		::glFramebufferTexture(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), ptex->object_name(), level);
	}

	void frame_buffer_attachment_point::attach(shared_texture_t & ptex, int level, tex2d_update_target tex_target, int layer) {
		mp_fbo->bind();
		if (ptex->type() == texture_type::TEX_1D) {
			::glFramebufferTexture1D(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), GLPP_CAST_TO_SCALAR(GLenum, tex_target), ptex->object_name(), level);
		} else if (ptex->type() == texture_type::TEX_2D) {
			::glFramebufferTexture2D(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), GLPP_CAST_TO_SCALAR(GLenum, tex_target), ptex->object_name(), level);
		} else if (ptex->type() == texture_type::TEX_3D) {
			::glFramebufferTexture3D(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), GLPP_CAST_TO_SCALAR(GLenum, tex_target), ptex->object_name(), level, layer);
		}
	}

	void frame_buffer_attachment_point::attach(shared_render_buffer_t prbo) {
		mp_fbo->bind();
		::glFramebufferRenderbuffer(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), GL_RENDERBUFFER,  prbo->object_name());
	}


	void frame_buffer_attachment_point::detach() {
		mp_fbo->bind();
		::glFramebufferRenderbuffer(GLPP_CAST_TO_SCALAR(GLenum, mp_fbo->target()), GLPP_CAST_TO_SCALAR(GLenum, m_point), GL_RENDERBUFFER,  0);
	}


	void frame_buffer_attachment_point::read_pixels(int x, int y, size_t width, size_t height, pixel_data_format format, fbo_pixel_type pix_type, void * dst) const{
		mp_fbo->bind();
		::glReadBuffer(GLPP_CAST_TO_SCALAR(GLenum, m_point));
		::glReadPixels(x, y, width, height, GLPP_CAST_TO_SCALAR(GLenum, format), GLPP_CAST_TO_SCALAR(GLenum, pix_type), dst);
	}

	frame_buffer::frame_buffer(frame_buffer_target target) :
	m_target(target){
		::glGenFramebuffers(1, &m_gl_name);
		assert_no_glerror("glGenFramebuffers failed. ");
	}

	frame_buffer::frame_buffer(name_type name, frame_buffer_target target) :
		m_target(target){
		m_gl_name = name;
	}

	frame_buffer::~frame_buffer() {
		if (::glIsFramebuffer(object_name()))
			::glDeleteFramebuffers(1, &m_gl_name);
	}

	void frame_buffer::bind() const{
		::glBindFramebuffer(GLPP_CAST_TO_SCALAR(GLenum, target()), object_name());
	}

	shared_frame_buffer_attachment_point_t frame_buffer::point(fbo_point point) {
		points_container_type::iterator it;
		if ((it = m_points.find(point)) != m_points.end())
			return it->second;

		return m_points[point] = shared_frame_buffer_attachment_point_t(new frame_buffer_attachment_point(this, point));
	}

	frame_buffer_status frame_buffer::status() const {
		bind();
		return GLPP_CAST_TO_SAFE_ENUM(frame_buffer_status, ::glCheckFramebufferStatus(GLPP_CAST_TO_SCALAR(GLenum, target())));
	}

	const frame_buffer & frame_buffer::window_default() {
		if (ms_window_fbo == NULL)
			ms_window_fbo = new frame_buffer(0, frame_buffer_target::DRAW);
		return *ms_window_fbo;
	}

	frame_buffer * frame_buffer::ms_window_fbo = NULL;
}
