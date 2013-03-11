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

#ifndef GLPP_PROGRAM_HPP_INCLUDED
#define GLPP_PROGRAM_HPP_INCLUDED

#include "shader.hpp"
#include "uniform.hpp"
#include "uniform_block.hpp"
#include "global_uniform.hpp"
#include <map>
#include <vector>

namespace glpp {

	//! Program that can be executed in the GPU pipeline
	/**
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_program
	 */
	struct program :
		public named_object<GLint>,
		public noncopyable{

		//! Construct an empty program
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCreateProgram.xml
		 */
		program();

		//! Destroy and release resources of program
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDeleteProgram.xml
		 */
		~program();

		//! Type of shaders container
		typedef std::vector<shared_shader_t> shaders_container_type;

		//! Attach a shader at program pipeline
		/**
		 * Shared pointer is kept till the shader is detached.
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glAttachShader.xml
		 * @see detach_shader()
		 */
		void attach_shader(const shared_shader_t & psh);

		//! Detach a shader object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDetachShader.xml
		 * @see attach_shader()
		 */
		void detach_shader(const shared_shader_t & psh);

		//! Get all attached shaders
		/**
		 * @ref exclusive_glpp_api attach_shader() detach_shader()
		 */
		inline shaders_container_type get_attached_shaders() const{
			return m_shaders;
		}

		//! Check if this program is linked
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLinkProgram.xml
		 */
		bool is_linked() const;

		//! Links a program object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLinkProgram.xml
		 */
		void link() throw(link_error);

		//! Compile shaders and link them
		/**
		 * This function will iterate through all shaders
		 * try to compile them, and then link them to final program.
		 * @ref exclusive_glpp_api attach_shader() detach_shader()
		 * @see shader::compile() link()
		 */
		void build() throw(compile_error, link_error);

		//! Validates a program object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glValidateProgram.xml
		 */
		void validate();

		//! Check if this program is valid
		/**
		 * This function will return the result of validate()
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glValidateProgram.xml
		 */
		bool is_valid() const;

		//! Returns the information log for a program object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgramInfoLog.xml
		 */
		const std::string info_log() const;

		//! Use this program for all future rendering calls
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glUseProgram.xml
		 */
		inline void use() const {
			::glUseProgram(object_name());
		}

		//! Get an active uniform variable declared in any place (in-block or global)
		/**
		 * This will return a @ref uniform object that can be used to query info about this variable.
		 * @return shared ptr to @ref uniform
		 * @see get_uniform(uniform::name_type)
		 */
		const shared_uniform_t & get_uniform(const std::string & name) throw (uniform_not_found);

		//! Check if there is uniform variable declared in any place (in-block or global)
		/**
		 * This will return true or false depending in the existence of object.
		 * @return bool
		 * @see get_uniform(std::string)
		 */
		const bool uniform_exists(const std::string & name);

		//! Get an active uniform variable declared in any place (in-block or global) by uniform index
		/**
		 * This will return a @ref uniform object that can be used to query info about this variable.
		 * @return shared ptr to @ref uniform
		 * @see get_uniform(const std::string &)
		 */
		const shared_uniform_t & get_uniform(uniform::name_type uniform_index) throw (uniform_not_found);

		//! Get an active uniform variable declared in global scope.
		/**
		 * This will return a @ref global_uniform object that can be used to query info and
		 * set the value of global variable.
		 * @return shared ptr to @ref global_uniform
		 * @throw uniform_not_found If there is no uniform with this name, or if it is not a variable of global scope.
		 */
		const shared_global_uniform_t & get_global_uniform(const std::string & name) throw (uniform_not_found);

		//! Get an active uniform block by name
		/**
		 * This will return a @ref uniform_block that can be used to query info and bind it to uniform @ref buffer objects
		 * * @return shared ptr to @ref uniform_block
		 * @see get_uniform_block(uniform_block::name_type)
		 */
		const shared_uniform_block_t & get_uniform_block(const std::string & bname) throw (uniform_not_found);

		//! Get an active uniform block by name
		/**
		 * This will return a uniform block that can be used to query info and bind it to uniform @ref buffer objects
		 * @return shared ptr to @ref uniform_block
		 * @see get_uniform_block(const std::string &)
		 */
		const shared_uniform_block_t & get_uniform_block(uniform_block::name_type id) throw (uniform_not_found);

		//! Bind a user-defined varying out variable to a fragment shader color number
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBindFragDataLocation.xml
		 */
		void bind_fragcolor_to_location(GLuint location, const std::string & name);

		//! Get total attached shaders
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint total_attached_shaders() const;

		//! Get total active atomic counter buffers
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint total_active_atomic_counter_buffers() const;

		//! Get total active attributes
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint total_active_attributes() const;

		//! Get the maximum name length of all active attributes (including null character)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint max_name_of_active_attributes() const;

		//! Get total number of active uniforms
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint total_active_uniforms() const;

		//! Get the maximum name length of all active uniforms (including null character)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint max_name_of_active_uniforms() const;

		//! Get total number of active uniform blocks
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint total_active_uniform_blocks() const;

		//! Get the maximum name length of all active uniform blocks(including null character)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint max_name_of_active_uniform_blocks() const;

		//! Get length of programs binary format
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint binary_length() const;

		//! Get program's feedback buffer mode
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		buffer_mode_type transform_feedback_buffer_mode() const;

		//! Get total transform feedback varyings
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint  total_transform_feedback_varyings() const;

		//! Get the maximum name length of all transform feedback varyings (including null character)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint max_name_of_transform_feedback_varying() const;

		//! Get the maximum geometry vertices that can be produced
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		GLuint max_geometry_vertices_out() const;

		//! Get the primitive type of geometry input
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		primitive_type geometry_input_type() const;

		//! Get the primitive type of geometry output
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetProgram.xml
		 */
		primitive_type geometry_output_type() const;

	protected:
		//! Type of uniforms container
		typedef std::map<uniform::name_type, shared_uniform_t> uniforms_container_type;

		//! Type of uniform blocks container
		typedef std::map<uniform_block::name_type, shared_uniform_block_t> uniform_blocks_container_type;

		//! Type of global uniforms container
		typedef std::map<uniform::name_type, shared_global_uniform_t> global_uniforms_container_type;

		//! Uniforms container
		uniforms_container_type m_uniforms;

		//! Global uniforms container
		global_uniforms_container_type m_global_uniforms;

		//! Uniform block container
		uniform_blocks_container_type m_uniform_blocks;

		//! Shaders container
		shaders_container_type m_shaders;

		/**
		 * @TODO: move them to types?
		 */
		GLPP_START_SAFE_ENUM(param_type)
			DELETE_STATUS = GL_DELETE_STATUS,
			LINK_STATUS = GL_LINK_STATUS,
			VALIDATE_STATUS = GL_VALIDATE_STATUS,
			INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
			ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
			// TODO: GLEW 1.7 ACTIVE_ATOMIC_COUNTER_BUFFERS = ACTIVE_ATOMIC_COUNTER_BUFFERS = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
			ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
			ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
			ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS,
			ACTIVE_UNIFORM_BLOCKS = GL_ACTIVE_UNIFORM_BLOCKS,
			ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
			ACTIVE_UNIFORM_MAX_LENGTH = GL_ACTIVE_UNIFORM_MAX_LENGTH,
			PROGRAM_BINARY_LENGTH = GL_PROGRAM_BINARY_LENGTH,
			TRANSFORM_FEEDBACK_BUFFER_MODE = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
			TRANSFORM_FEEDBACK_VARYINGS = GL_TRANSFORM_FEEDBACK_VARYINGS,
			TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
			GEOMETRY_VERTICES_OUT = GL_GEOMETRY_VERTICES_OUT,
			GEOMETRY_INPUT_TYPE = GL_GEOMETRY_INPUT_TYPE,
			GEOMETRY_OUTPUT_TYPE = GL_GEOMETRY_OUTPUT_TYPE
		GLPP_END_SAFE_ENUM(param_type)

		//! Get a program parameter
		GLint get_param(param_type type) const;
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
	//void bind_to(GLuint colnum, const std::string & var_name, program * pprog, frame_buffer * pfbo) throw (std::invalid_argument);
}

#endif
