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
#include "buffer.hpp"
#include "exception.hpp"

namespace glpp{


	buffer::buffer(buffer_type type)
		:m_buf_type(type),
		 m_size(0)	 {
		::glGenBuffers(1, &m_gl_name);
		assert_no_glerror("glGenBuffers failed.");
	}

	buffer::~buffer() {
		if (::glIsBuffer(m_gl_name)) {
			::glDeleteBuffers(1, &m_gl_name);
		}
	}

	void buffer::define_data(size_t size, const void * pdata, buffer_usage_pattern usage) {
		bind();
		m_size = size;
		::glBufferData(GLPP_CAST_TO_SCALAR(GLenum, type()), size, pdata, GLPP_CAST_TO_SCALAR(GLenum, usage));
	}

	void buffer::update_subdata(size_t offset, size_t size, const void * pdata) {
		bind();
		::glBufferSubData(GLPP_CAST_TO_SCALAR(GLenum, type()), offset, size, pdata);
	}

	std::vector<uint8_t> buffer::get_data(size_t offset, size_t size) {
		bind();
		std::vector<uint8_t> buf(size);
		::glGetBufferSubData(GLPP_CAST_TO_SCALAR(GLenum, type()), offset, size, &buf[0]);
#		if (GLPP_LANG == GLPP_LANG_CXX11)
			return std::move(buf);
#		else
			return buf;
#		endif
	}

	void * buffer::map_data(buffer_access_mode access) {
		bind();
		return ::glMapBuffer(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, access));
	}

	bool buffer::unmap_data() {
		bind();
		return (bool)::glUnmapBuffer(GLPP_CAST_TO_SCALAR(GLenum, type()));
	}

	void * buffer::map_data_range(size_t offset, size_t size, map_access_bit access) {
		bind();
		return ::glMapBufferRange(GLPP_CAST_TO_SCALAR(GLenum,  type()), offset, size,GLPP_CAST_TO_SCALAR(GLenum, access));
	}

	void buffer::flush_mapped_range(size_t offset, size_t size) {
		bind();
		::glFlushMappedBufferRange(GLPP_CAST_TO_SCALAR(GLenum, type()), offset, size);
	}
}
