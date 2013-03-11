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
#include "uniform.hpp"
#include "program.hpp"

namespace glpp {

	uniform::uniform(program * pprog, const std::string & name, name_type uniform_index) :
		mp_program(pprog),
		m_var_name(name),
		m_info_fetched(false){

		m_gl_name = uniform_index;
	}

	void uniform::query_info() const{

		if (!m_info_fetched) {
			GLint size;
			GLenum type;

			::glGetActiveUniform(mp_program->object_name(), object_name(), 0, 0, &size, &type, NULL);
			const_cast<uniform *>(this)->m_size = size;
			const_cast<uniform *>(this)->m_type = GLPP_CAST_TO_SAFE_ENUM(variable_type, type);

			name_type name_id[1] = { object_name() };
			GLint val;
			::glGetActiveUniformsiv(mp_program->object_name(), 1, name_id, GL_UNIFORM_ARRAY_STRIDE, &val);
			const_cast<uniform *>(this)->m_array_stride = val;

			val = 0;
			::glGetActiveUniformsiv(mp_program->object_name(), 1, name_id, GL_UNIFORM_ARRAY_STRIDE, &val);
			const_cast<uniform *>(this)->m_matrix_stride = val;

			val = 0;
			::glGetActiveUniformsiv(mp_program->object_name(), 1, name_id, GL_UNIFORM_OFFSET, &val);
			const_cast<uniform *>(this)->m_offset = val;

			val = 0;
			::glGetActiveUniformsiv(mp_program->object_name(), 1, name_id, GL_UNIFORM_IS_ROW_MAJOR, &val);
			const_cast<uniform *>(this)->m_is_row_major = val;

			val = -1;
			::glGetActiveUniformsiv(mp_program->object_name(), 1, name_id, GL_UNIFORM_BLOCK_INDEX, &val);
			if (val != -1) {
				const_cast<uniform *>(this)->m_owner_block = const_cast<uniform *>(this)->mp_program->get_uniform_block(val);
			}
			const_cast<uniform *>(this)->m_is_row_major = val;

			const_cast<uniform *>(this)->m_info_fetched = true;
		}
	}

	size_t uniform::offset() const {
		query_info();
		return m_offset;
	}

	size_t uniform::size() const{
		query_info();
		return m_size;
	}

	size_t uniform::array_stride() const{
		query_info();
		return m_array_stride;
	}

	size_t uniform::matrix_stride() const{
		query_info();
		return m_matrix_stride;
	}

	variable_type uniform::type() const{
		query_info();
		return m_type;
	}

	bool uniform::is_row_major() const {
		query_info();
		return m_is_row_major;
	}

	const shared_uniform_block_t & uniform::owner_block() const throw(exception) {
		query_info();
		if (! m_owner_block) {
			throw exception("Cannot get the uniform block of a global uniform variable.");
		}
		return m_owner_block;
	}
}
