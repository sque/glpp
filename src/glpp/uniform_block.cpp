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
#include "uniform_block.hpp"
#include "program.hpp"
#include "buffer.hpp"

namespace glpp {

	uniform_block::uniform_block(const program * pprog, const std::string & name, name_type bid):
		m_block_name(name),
		mp_program(pprog),
		m_info_fetched(false){
		m_gl_name = bid;
	}

	void uniform_block::bind_to_point(GLuint point) {
		glUniformBlockBinding(mp_program->object_name(), object_name(), point);
	}

	// Helper function to get uniform block parameters
	template<class Ret>
	Ret _uniform_block_get_param(const uniform_block & block, uniform_block_param param) {
		GLint bpoint;
		glGetActiveUniformBlockiv(block.owner_program().object_name(), block.object_name(), GLPP_CAST_TO_SCALAR(GLenum, param), &bpoint);
		return static_cast<Ret>(bpoint);
	}

	GLuint uniform_block::get_binding_point() const {
		return _uniform_block_get_param<GLuint>(*this, uniform_block_param::BINDING);
	}

	size_t uniform_block::data_size() const {
		return _uniform_block_get_param<size_t>(*this, uniform_block_param::DATA_SIZE);
	}

	size_t uniform_block::total_active_uniforms() const {
		return _uniform_block_get_param<size_t>(*this, uniform_block_param::ACTIVE_UNIFORMS);
	}

	bool uniform_block::is_referenced_by_vertex_shader() const {
		return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_VERTEX_SHADER);
	}

	bool uniform_block::is_referenced_by_fragment_shader() const {
		return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_FRAGMENT_SHADER);
	}

	bool uniform_block::is_referenced_by_geometry_shader() const {
		return _uniform_block_get_param<bool>(*this, uniform_block_param::REFERENCED_BY_GEOMETRY_SHADER);
	}

	void bind_to(GLuint point, uniform_block * pblock, buffer * pbuffer) throw (std::invalid_argument){
		pblock->bind_to_point(point);
		if (pbuffer->type() != glpp::buffer_type::UNIFORM)
			throw std::invalid_argument("Uniform blocks can only be bound with buffers of UNIFORM type.");
		pbuffer->bind_to_point(point);
	}

}
