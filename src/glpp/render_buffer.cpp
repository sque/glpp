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
#include "render_buffer.hpp"

namespace glpp{

	render_buffer::render_buffer() {
		::glGenRenderbuffers(1, &m_gl_name);
		assert_no_glerror("glGenRenderbuffers failed. ");
	}

	render_buffer::render_buffer(
			image_rendable_format internal_format,
			size_t width,
			size_t height,
			size_t samples) throw(gl_error) {

		::glGenRenderbuffers(1, &m_gl_name);
		assert_no_glerror("glGenRenderbuffers failed. ");
		define_storage(internal_format, width, height, samples);
	}

	render_buffer::~render_buffer() {
		if (::glIsRenderbuffer(object_name())) {
			::glDeleteRenderbuffers(1, &m_gl_name);
		}
	}

	void render_buffer::bind() {
		::glBindRenderbuffer(GL_RENDERBUFFER, object_name());
	}

	void render_buffer::define_storage(image_rendable_format internal_format, size_t width, size_t height, size_t samples) throw(gl_error) {
		bind();
		::glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GLPP_CAST_TO_SCALAR(GLenum, internal_format), width, height);
		assert_no_glerror("glRenderbufferStorageMultisample failed.");
	}
}
