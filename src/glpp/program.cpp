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
#include "program.hpp"
#include <stdio.h>

namespace glpp{

	program::program(){
		m_gl_name = ::glCreateProgram();
		if (m_gl_name == 0)
			throw gl_error(glGetError(), "Cannot create shader program.");
	}

	program::~program() {
		if (::glIsProgram(object_name()))
			::glDeleteProgram(object_name());
	}

	void program::attach_shader(const shared_shader_t & psh) {
		::glAttachShader(m_gl_name, psh->object_name());
		assert_no_glerror("glAttachShader failed.");
		m_shaders.push_back(psh);
	}

	void program::detach_shader(const shared_shader_t & psh) {
		shaders_container_type::iterator it = std::find(m_shaders.begin(), m_shaders.end(), psh);

		if (it == m_shaders.end())
			return;	// Not found

		::glDetachShader(object_name(), psh->object_name());
		m_shaders.erase(it);
	}

	int program::get_param(param_type type) const {
		GLint param_val;
		::glGetProgramiv(m_gl_name, GLPP_CAST_TO_SCALAR(GLenum, type), &param_val);
		return param_val;
	}

	const shared_uniform_t & program::get_uniform(const std::string & uname) throw (uniform_not_found){
		uniform::name_type uniform_index = GL_INVALID_INDEX;
		const char * names = uname.c_str();
		::glGetUniformIndices(object_name(), 1, &names, &uniform_index);
		if (uniform_index == GL_INVALID_INDEX)
			throw uniform_not_found(uname);

		uniforms_container_type::iterator it;
		if ((it = m_uniforms.find(uniform_index)) == m_uniforms.end()) {
			// Create uniform state object
			m_uniforms[uniform_index] = shared_uniform_t(new uniform(this, uname, uniform_index));
		}

		return m_uniforms[uniform_index];
	}

	const bool program::uniform_exists(const std::string & uname) {
		uniform::name_type uniform_index = GL_INVALID_INDEX;
		const char * names = uname.c_str();
		::glGetUniformIndices(object_name(), 1, &names, &uniform_index);
		if (uniform_index == GL_INVALID_INDEX)
			return false;
		return true;
	}

	const shared_uniform_t & program::get_uniform(uniform::name_type uniform_index) throw (uniform_not_found) {

		uniforms_container_type::iterator it;
		if ((it = m_uniforms.find(uniform_index)) == m_uniforms.end()) {
			std::string error_str(100, ' ');
			snprintf(const_cast<char *>(error_str.c_str()), error_str.size(), "by uniform index[%u]", uniform_index);
			throw uniform_not_found(error_str);
		}

		return m_uniforms[uniform_index];
	}

	const shared_global_uniform_t & program::get_global_uniform(const std::string & name) throw (uniform_not_found) {

		shared_uniform_t uni = get_uniform(name);	// Get general uniform type

		global_uniforms_container_type::iterator it;
		if ((it = m_global_uniforms.find(uni->object_name())) == m_global_uniforms.end()) {

			// Find uniform store location
			GLint location = ::glGetUniformLocation(this->object_name(), name.c_str());
			if (location == -1)
				throw uniform_not_found(name);

			// Register global uniform
			m_global_uniforms[uni->object_name()] = shared_global_uniform_t(new global_uniform(this, name, uni->object_name(), location));
		}
		return m_global_uniforms[uni->object_name()];
	}

	const shared_uniform_block_t & program::get_uniform_block(const std::string & bname) throw (uniform_not_found){
		uniform_block::name_type bid = ::glGetUniformBlockIndex(object_name(), bname.c_str());
		if (bid == GL_INVALID_INDEX)
			throw uniform_not_found(bname);

		uniform_blocks_container_type::iterator it;
		if ((it = m_uniform_blocks.find(bid)) == m_uniform_blocks.end()) {
			// Create uniform state object
			return m_uniform_blocks[bid] = shared_uniform_block_t(new uniform_block(this, bname, bid));
		}
		return it->second;
	}

	const shared_uniform_block_t & program::get_uniform_block(uniform_block::name_type bid) throw (uniform_not_found) {

		uniform_blocks_container_type::iterator it;
		if ((it = m_uniform_blocks.find(bid)) == m_uniform_blocks.end()) {

			if (bid >= total_active_uniform_blocks()) {
				std::string error_str(100, ' ');
				snprintf(const_cast<char *>(error_str.c_str()), error_str.size(), "by uniform block index[%u]", bid);
				throw uniform_not_found(error_str);
			}

			std::string buf_name(255, ' ');
			GLsizei bfsize;
			glGetActiveUniformBlockName(
					object_name(),
					bid,
					255,
					&bfsize,
					const_cast<char *>(buf_name.c_str()));

			// Create uniform state object
			return m_uniform_blocks[bid] = shared_uniform_block_t(new uniform_block(this, buf_name, bid));
		}

		return it->second;
	}

	void program::bind_fragcolor_to_location(GLuint location, const std::string & name) {
		::glBindFragDataLocation(object_name(), 0, name.c_str());
	}

	bool program::is_linked() const{
		return static_cast<bool>(get_param(param_type::LINK_STATUS));
	}

	bool program::is_valid() const {
		return static_cast<bool>(get_param(param_type::VALIDATE_STATUS));
	}

	GLuint program::total_attached_shaders() const {
		return static_cast<GLuint>(get_param(param_type::ATTACHED_SHADERS));
	}

	GLuint program::total_active_atomic_counter_buffers() const {
		//TODO: GLEW 1.7 return get_param(param_type::ACTIVE_ATOMIC_COUNTER_BUFFERS);
		return 0;
	}

	GLuint program::total_active_attributes() const{
		return static_cast<GLuint>(get_param(param_type::ACTIVE_ATTRIBUTES));
	}

	GLuint program::max_name_of_active_attributes() const{
		return static_cast<GLuint>(get_param(param_type::ACTIVE_ATTRIBUTE_MAX_LENGTH));
	}

	GLuint program::total_active_uniforms() const{
		return static_cast<GLuint>(get_param(param_type::ACTIVE_UNIFORMS));
	}

	GLuint program::max_name_of_active_uniforms() const{
		return static_cast<GLuint>(get_param(param_type::ACTIVE_UNIFORM_MAX_LENGTH));
	}

	GLuint program::total_active_uniform_blocks() const {
		return static_cast<GLuint>(get_param(param_type::ACTIVE_UNIFORM_BLOCKS));
	}

	GLuint program::max_name_of_active_uniform_blocks() const {
		return static_cast<GLuint>(get_param(param_type::ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH));
	}

	GLuint program::binary_length() const{
		return static_cast<GLuint>(get_param(param_type::PROGRAM_BINARY_LENGTH));
	}

	buffer_mode_type program::transform_feedback_buffer_mode() const{
		return GLPP_CAST_TO_SAFE_ENUM(buffer_mode_type, get_param(param_type::TRANSFORM_FEEDBACK_BUFFER_MODE));
	}

	GLuint program::total_transform_feedback_varyings() const{
		return static_cast<GLuint>(get_param(param_type::TRANSFORM_FEEDBACK_VARYINGS));
	}

	GLuint program::max_name_of_transform_feedback_varying() const{
		return static_cast<GLuint>(get_param(param_type::TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH));
	}

	GLuint program::max_geometry_vertices_out() const{
		return static_cast<GLuint>(get_param(param_type::GEOMETRY_VERTICES_OUT));
	}

	primitive_type program::geometry_input_type() const{
		return GLPP_CAST_TO_SAFE_ENUM(primitive_type, get_param(param_type::GEOMETRY_INPUT_TYPE));
	}

	primitive_type program::geometry_output_type() const{
		return GLPP_CAST_TO_SAFE_ENUM(primitive_type, get_param(param_type::GEOMETRY_OUTPUT_TYPE));
	}

	const std::string program::info_log() const{
		int info_lenght = get_param(param_type::INFO_LOG_LENGTH);

		// Read error
		std::string info_log(info_lenght, '\0');
		glGetProgramInfoLog(m_gl_name, info_lenght, &info_lenght, &info_log[0]);
#	if	(GLPP_LANG == GLPP_LANG_CXX11)
		return std::move(info_log);
#	else
		return info_log;
#	endif
	}

	void program::link() throw(link_error){
		::glLinkProgram(m_gl_name);
		if (!is_linked()) {
			throw link_error(info_log());
		}
	}

	void program::build() throw(compile_error, link_error) {
		shaders_container_type::iterator it;

		for(it = m_shaders.begin(); it != m_shaders.end(); it ++) {
			if (!(*it)->is_compiled()) {
				(*it)->compile();
			}
		}
		link();
	}

	void program::validate(){
		::glValidateProgram(m_gl_name);
		if (!is_valid()) {
			throw link_error(info_log()); // TODO: another exception class
		}
	}

	/*void bind_to(GLuint colnum, const std::string & var_name, program * pprog, frame_buffer * pfbo) throw (std::invalid_argument) {
		pprog->bind_fragcolor_to_location(colnum, name);
		pfbo->bind
	}*/
}
