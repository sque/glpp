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

#ifndef GLPP_UNIFORM_BLOCK_HPP_INCLUDED
#define GLPP_UNIFORM_BLOCK_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Active uniform block of a program
	/**
	 * Uniforms that do not belong to any @ref uniform_block, belong to global scope.
	 * These variable values must be set manually, one by one.
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_program
	 * @see program::get_uniform_block()
	 */
	struct uniform_block :
		public named_object<GLuint>,
		public noncopyable {


		//! All uniforms belong and are managed by a @ref program object.
		friend class program;

		//! The GLSL name of this block
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockName.xml
		 */
		const std::string & block_name() {
			return m_block_name;
		}

		//! Bind/Link this block to a binding point
		/**
		 * The same indexed position should be used by buffer::bind_to_point()
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glUniformBlockBinding.xml
		 * @see bind()
		 */
		void bind_to_point(GLuint point);

		//! Get the point that it is bound to
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 * @see bind_to_point()
		 */
		GLuint get_binding_point() const;

		//! Get in-GPU memory size of this uniform block
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 */
		size_t data_size() const;

		//! Get total number of active uniforms
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 */
		size_t total_active_uniforms() const;

		// TODO: get_active_uniform() it return indices. Can this be translated to uniform locations and thus objects?

		//! Check if block is referenced by vertex shader
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 */
		bool is_referenced_by_vertex_shader() const;

		//! Check if block is referenced by fragment shader
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 */
		bool is_referenced_by_fragment_shader() const;

		//! Check if block is referenced by geometry shader
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetActiveUniformBlockiv.xml
		 */
		bool is_referenced_by_geometry_shader() const;

		//! Get @ref program that this uniform belongs to.
		const program & owner_program() const {
			return *mp_program;
		}

	protected:
		//! Constructed only be program
		uniform_block(const program * pprog, const std::string & name, name_type bid);

		//! Block name
		std::string m_block_name;

		//! Program that uniform belongs at
		const program * mp_program;

		//! Flag if information has been fetched
		bool m_info_fetched;

		//! Variable size
		size_t m_size;

		//! Variable type;
		variable_type m_type;

		//! Actually request uniform block information
		void query_info();
	};

	//! Bind a @ref uniform_block and a uniform @ref buffer object to common point
	/**
	 * @ingroup gpu_program
	 * @param point The point to bind both objects. If something else is binded there,
	 * 	it will be overwritten
	 * @param pblock Pointer to uniform_block that will binded with the uniform @ref buffer object.
	 * @param pbuffer Pointer to uniform @ref buffer object. This object will be checked that it
	 * is of type() uniform.
	 * @throw std::invalid_argument If the pbuffer is not of uniform type.
	 * @see uniform_block::bind_to_point(), buffer::bind_to_point()
	 */
	void bind_to(GLuint point, uniform_block * pblock, buffer * pbuffer) throw (std::invalid_argument);
}

#endif
