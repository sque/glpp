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

#ifndef GLPP_SHADER_HPP_INCLUDED
#define GLPP_SHADER_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Exception thrown when shader compilation has failed.
	/**
	 * @ingroup exceptions
	 */
	struct shader_compile_error: public compile_error {
		//! Construct passing reference to shader
		/**
		 * Message will include the info_log() from compilation
		 */
		shader_compile_error(const shader & sh) throw ();

		//! Class is inheritable
		virtual ~shader_compile_error() throw () {	}

		//! Return reference to shader
		const shader & shader_object() const {
			return m_shader;
		}

	protected:

		//! Storage of shader reference
		const shader & m_shader;
	};

	//! GPU Shader object
	/**
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_program
	 */
	struct shader:
		public named_object<GLint>,
		public noncopyable{

		//! Construct from source
		/**
		 * @param type Type of this shader (Fragment, Geometry .. )
		 * @param source The GLSL source code of this shader.
		 */
		shader(shader_type type, const std::string & source);

		//! Destroy and release shader
		~shader();

		//! Get GLSL source code of this shader
		const std::string & source() const {
			return m_source;
		}

		//! Get reference to GLSL source code of this shader
		/**
		 * Changing source code has effect only if the object
		 * is not compiled yet.
		 */
		std::string & source() {
			return m_source;
		}

		//! Compile this shader to shader object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCompileShader.xml
		 */
		void compile() throw(compile_error);

		//! Return true only if it is compiled successfully.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCompileShader.xml
		 * @see compile()
		 */
		bool is_compiled() const;

		//! Get the information log about compilation of this shader
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetShaderInfoLog.xml
		 * @see compile(), is_compiled()
		 */
		std::string info_log() const;

		//! Get the type of this shader
		const shader_type & type() const{
			return m_type;
		}

	protected:

		//! Generic initialize function
		void initialize();

		//! Type of this shader (Fragment, Geometry .. )
		shader_type m_type;

		//! Source code of this shader
		std::string m_source;
	};

	//! Create shader object from in-file source code.
	/**
	 * @param type Type of the shader to create
	 * @param fname Filename where GLSL source code resides
	 * @throw std::invalid_argument If the file cannot be accessed.
	 * @ingroup gpu_program
	 * @see open_shader_files()
	 */
	shared_shader_t open_shader_file(shader_type type, const std::string fname);

#if (GLPP_LANG == GLPP_LANG_CXX11) || (GLPP_LANG == GLPP_LANG_CXX0X)
	//! Create shader object from multiple GLSL source files.
	/**
	 * @param type Type of the shader to create
	 * @param fnames Filenames where GLSL source code resides. The order of file is important,
	 * as in the same order the source code will be concatenated.
	 * @throw std::invalid_argument If any of the files cannot be accessed.
	 * @ingroup gpu_program
	 * @see open_shader_file()
	 */
	shared_shader_t open_shader_files(shader_type type, std::initializer_list<const std::string> fnames);
#endif
}

#endif
