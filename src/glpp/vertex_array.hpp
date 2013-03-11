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

#ifndef GLPP_VERTEX_ARRAY_HPP_INCLUDED
#define GLPP_VERTEX_ARRAY_HPP_INCLUDED

#include "base.hpp"
#include "buffer.hpp"
#include <map>

namespace glpp {

	//! Attribute of a vertex array object
	/**
	 * This interface permits to query and manage an attribute
	 * of a vertex array object.
	 * @remarks non-copyable, non-inheritable, RAII
	 */
	struct vertex_attrib_array:
		public noncopyable {

		//! All attributes belong and are managed by a @ref vertex_array object.
		friend class vertex_array;

		//! Enable usage of this attribute
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glEnableVertexAttribArray.xml
		 */
		void enable();

		//! Disable usage of this attribute
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glEnableVertexAttribArray.xml
		 */
		void disable();

		//! Check if this attribute is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetVertexAttrib.xml
		 */
		bool is_enabled() const;

		//! Define where data are stored for this attribute
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glVertexAttrib.xml
		 */
		void set_pointerf(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		//! Define where data are stored for this attribute
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glVertexAttrib.xml
		 */
		void set_pointeri(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		//! Define where data are stored for this attribute
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glVertexAttrib.xml
		 */
		void set_pointerl(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride = 0, size_t offset = 0);

		//! Get the index of this attribute
		inline GLuint index() const{
			return m_attr_index;
		}

		//! Get @ref vertex_array that this attribute belongs to.
		const vertex_array & owner_vertex_array() const {
			return *mp_vao;
		}

	protected:

		//! Constructor is only called by @ref vertex_array owner
		vertex_attrib_array(const vertex_array * pvao, GLuint index);

		//! Pointer to owner object of this attributes;
		const vertex_array * mp_vao;

		//! Index of this attribute
		GLuint m_attr_index;

		//! Enumeration of all parameters of an attribute
		GLPP_START_SAFE_ENUM(param_type)
			BUFFER_BINDING = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
			ENABLED = GL_VERTEX_ATTRIB_ARRAY_ENABLED,
			SIZE = GL_VERTEX_ATTRIB_ARRAY_SIZE,
			STRIDE = GL_VERTEX_ATTRIB_ARRAY_STRIDE,
			TYPE = GL_VERTEX_ATTRIB_ARRAY_TYPE,
			NORMALIZED = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
			INTEGER = GL_VERTEX_ATTRIB_ARRAY_INTEGER,
			DIVISOR = GL_VERTEX_ATTRIB_ARRAY_DIVISOR,
			CURRENT = GL_CURRENT_VERTEX_ATTRIB,
		GLPP_END_SAFE_ENUM(param_type)
	};

	//! Object to handle a vertex array object.
	/**
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_buffer
	 * @todo Implement Draw*Indirect
	 * @todo Implement Draw*BaseInstance
	 * @todo Implement Draw*OneInstance
	 * @todo Implement MultiDraw*OneInstance
	 */
	struct vertex_array :
		public named_object<GLuint>,
		noncopyable {

		//! Construct an empty vertex array object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGenBuffers.xml
		 */
		vertex_array(primitive_type primitives = primitive_type::TRIANGLES);

		//! Destroy this vertex array object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDeleteVertexArrays.xml
		 */
		~vertex_array();

		//! Bind this buffer as active vertex array object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBindVertexArray.xml
		 */
		inline void bind() const {
			::glBindVertexArray(object_name());
		}

		//! Access properties object of an attribute (by index)
		/**
		 * @param index The index of attribute to access
		 */
		shared_vertex_attrib_array_t & attrib(GLuint index);

		//! Set primitive type when drawing
		void set_primitive(primitive_type mode);

		//! Get primitive type when drawing
		primitive_type get_primitive() const;

		//! Draw this vertex array
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawArrays.xml
		 * @see set_primitive()
		 */
		void draw(GLint first, GLint count);

		//! Draw this vertex array using vertex indices (GLubyte)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElements.xml
		 * @see set_primitive()
		 */
		void draw_elements(GLint count, const GLubyte * pindices);

		//! Draw this vertex array using vertex indices (GLushort)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElements.xml
		 * @see set_primitive()
		 */
		void draw_elements(GLint count, const GLushort * pindices);

		//! Draw this vertex array using vertex indices (GLuint)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElements.xml
		 * @see set_primitive()
		 */
		void draw_elements(GLint count, const GLuint * pindices);

		//! Draw this vertex array using vertex indices (Elements array @ref buffer object )
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElements.xml
		 * @see buffer
		 * @see set_primitive()
		 */
		void draw_elements(GLint count, const buffer & elem_array, elements_type type);

		//! Draw this vertex array multiple times (instanced)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawArraysInstanced.xml
		 * @see set_primitive()
		 */
		void draw_instances(GLint first, GLint count, GLint instances);

		//! Draw this vertex array using vertex indices (GLubyte), multiple times (instanced)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElementsInstanced.xml
		 * @see set_primitive()
		 */
		void draw_elements_instances(GLint count, const GLubyte * pindices, GLint instances);

		//! Draw this vertex array using vertex indices (Gushort), multiple times (instanced)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElementsInstanced.xml
		 * @see set_primitive()
		 */
		void draw_elements_instances(GLint count, const GLushort * pindices, GLint instances);

		//! Draw this vertex array using vertex indices (GLint), multiple times (instanced)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElementsInstanced.xml
		 * @see set_primitive()
		 */
		void draw_elements_instances(GLint count, const GLuint * pindices, GLint instances);

		//! Draw this vertex array using vertex indices (@ref buffer object), multiple times (instanced)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDrawElementsInstanced.xml
		 * @see buffer
		 * @see set_primitive()
		 */
		void draw_elements_instances(GLint count,  const buffer & elem_array, elements_type type, GLint instances);

	protected:

		//! Type of attributes container
		typedef std::map<GLint, shared_vertex_attrib_array_t> attribs_container_type;

		//! Map with all attributes
		attribs_container_type m_attribs;

		//! Primitive type when drawing
		primitive_type m_primitives;
	};
}

#endif
