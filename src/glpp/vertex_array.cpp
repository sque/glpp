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
#include "vertex_array.hpp"
#include <assert.h>

namespace glpp {

	vertex_attrib_array::vertex_attrib_array(const vertex_array * pvao, GLuint index) :
		mp_vao(pvao),
		m_attr_index(index){
	}

	void vertex_attrib_array::enable(){
		mp_vao->bind();
		::glEnableVertexAttribArray(index());
	}

	void vertex_attrib_array::disable(){
		mp_vao->bind();
		::glDisableVertexAttribArray(index());
	}

	bool vertex_attrib_array::is_enabled() const{
		mp_vao->bind();
		return gl_get_wrapper<bool>(glGetVertexAttribiv, index(), param_type::ENABLED);
	}

	void vertex_attrib_array::set_pointerf(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribPointer(index(), vector_size, GLPP_CAST_TO_SCALAR(GLenum, bo_type), GL_FALSE, stride, (void*)offset);
	}

	void vertex_attrib_array::set_pointeri(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribIPointer(index(), vector_size, GLPP_CAST_TO_SCALAR(GLenum, bo_type), stride, (void*)offset);
	}

	void vertex_attrib_array::set_pointerl(const buffer & bo, GLint vector_size, attribf_data_type bo_type, size_t stride, size_t offset) {
		assert(bo.type() == buffer_type::ARRAY);
		bo.bind();
		mp_vao->bind();
		::glVertexAttribIPointer(index(), vector_size, GLPP_CAST_TO_SCALAR(GLenum, bo_type), stride, (void*)offset);
	}

	vertex_array::vertex_array(primitive_type primitives):
		m_primitives(primitives){
		::glGenVertexArrays(1, &m_gl_name);
	}

	vertex_array::~vertex_array() {
		if (::glIsVertexArray(m_gl_name)) {
			::glDeleteVertexArrays(1, &m_gl_name);
		}
	}

	shared_vertex_attrib_array_t & vertex_array::attrib(GLuint index) {
		attribs_container_type::iterator it = m_attribs.find(index);

		if (it == m_attribs.end()) {
			// Create new object
			m_attribs[index] = shared_vertex_attrib_array_t(new vertex_attrib_array(this, index));
		}
		return m_attribs[index];
	}

	void vertex_array::draw(GLint first, GLint count) {
		bind();
		::glDrawArrays(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), first, count);
	}

	void vertex_array::draw_elements(GLint count, const GLubyte * pindices) {
		bind();
		::glDrawElements(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_BYTE, pindices);
	}

	void vertex_array::draw_elements(GLint count, const GLushort * pindices) {
		bind();
		::glDrawElements(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_SHORT, pindices);
	}

	void vertex_array::draw_elements(GLint count, const GLuint * pindices) {
		bind();
		::glDrawElements(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_INT, pindices);
	}

	void vertex_array::draw_elements(GLint count, const buffer & elem_array, elements_type type) {
		bind();
		elem_array.bind();
		::glDrawElements(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GLPP_CAST_TO_SCALAR(GLenum, type), NULL);
	}

	void vertex_array::draw_instances(GLint first, GLint count, GLint instances) {
		bind();
		::glDrawArraysInstanced(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), first, count, instances);
	}

	void vertex_array::draw_elements_instances(GLint count, const GLubyte * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_BYTE, pindices, instances);
	}

	void vertex_array::draw_elements_instances(GLint count, const GLushort * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_SHORT, pindices, instances);
	}

	void vertex_array::draw_elements_instances(GLint count, const GLuint * pindices, GLint instances) {
		bind();
		::glDrawElementsInstanced(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GL_UNSIGNED_INT, pindices, instances);
	}

	void vertex_array::draw_elements_instances(GLint count,  const buffer & elem_array, elements_type type, GLint instances) {
		bind();
		elem_array.bind();
		::glDrawElementsInstanced(GLPP_CAST_TO_SCALAR(GLenum, m_primitives), count, GLPP_CAST_TO_SCALAR(GLenum, type), NULL, instances);
	}

}
