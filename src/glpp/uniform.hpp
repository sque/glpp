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

#ifndef GLPP_UNIFORM_HPP_INCLUDED
#define GLPP_UNIFORM_HPP_INCLUDED

#include "base.hpp"
#include "uniform_block.hpp"

namespace glpp {

	//! Query object for active uniform variable
	/**
	 * This interface permits querying information about any type
	 * of uniform variable. If you want to set a value of a global uniform
	 * variable (not in uniform block) see @ref global_uniform.
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_program
	 * @see program::get_uniform(), program::get_global_uniform()
	 */
	struct uniform :
		public named_object<GLuint>,
		public noncopyable{

		//! All uniforms belong and are managed by a @ref program object.
		friend class program;

		//! Get GLSL variable name of this uniform
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		const std::string & var_name() const{
			return m_var_name;
		}

		//! Get in-GPU memory size of uniform variable
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		size_t size() const;

		//! Get in-GPU memory offset from beginning of uniform block.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		size_t offset() const;

		//! Get data type of uniform variable
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		variable_type type() const;

		//! The stride of array for in-GPU storage
		/**
		 * This is only valid for array uniform variables.
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		size_t array_stride() const;

		//! The stride of matrix for in-GPU storage
		/**
		 * This is only valid for matrix uniform variables.
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		size_t matrix_stride() const;

		//! Check if matrix is stored in row major layout.
		/**
		 * This is only valid for matrix uniform variables.
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 */
		bool is_row_major() const;

		//! Get shared point to @ref uniform_block owner (if any).
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformsiv.xml
		 * @throw exception If this variable does not belong to a @ref uniform_block.
		 */
		const shared_uniform_block_t & owner_block() const throw(exception);

		//! Get @ref program that this uniform belongs to.
		const program & owner_program() const {
			return *mp_program;
		}

	protected:

		//! Constructed only by program
		uniform(program * pprog, const std::string & name, name_type uniform_index);

		//! Program that uniform belongs at
		program * mp_program;

	private:

		//! In GLSL source variable name
		std::string m_var_name;

		//! Flag if information has been fetched
		bool m_info_fetched;

		//! Variable size
		size_t m_size;

		//! Storage memory offset
		size_t m_offset;

		//! Variable array stride
		size_t m_array_stride;

		//! Variable matrix stride
		size_t m_matrix_stride;

		//! If matrix is row major
		bool m_is_row_major;

		//! Variable type;
		variable_type m_type;

		//! Pointer to uniform block owner.
		shared_uniform_block_t m_owner_block;

		//! Actually request variable information
		void query_info() const;
	};
}

#endif
