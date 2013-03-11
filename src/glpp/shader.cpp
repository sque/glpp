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
#include "shader.hpp"
#include "exception.hpp"
#include <iostream>
#include <fstream>

namespace glpp{

	shader_compile_error::shader_compile_error(const shader & sh) throw () :
		compile_error(sh.info_log()),
		m_shader(sh){}

	void shader::initialize() {
		m_gl_name = ::glCreateShader(GLPP_CAST_TO_SCALAR(GLenum, m_type));
		if (m_gl_name == 0)
			throw gl_error(glGetError(), "Cannot create shader.");
	}

	shader::shader(shader_type type, const std::string & source):
		m_type(type),m_source(source) {
		initialize();
	}

	shader::~shader() {
		if (::glIsShader(m_gl_name))
			::glDeleteShader(m_gl_name);
	}

	std::string shader::info_log() const{
		int info_lenght = 0;
		::glGetShaderiv(m_gl_name, GL_INFO_LOG_LENGTH, &info_lenght);

		// Read error
		std::string info_log(info_lenght, '\0');
		::glGetShaderInfoLog(m_gl_name, info_lenght, &info_lenght, &info_log[0]);
		return info_log;
	}

	bool shader::is_compiled() const {
		GLint is_compiled_flag = 0;
		::glGetShaderiv(m_gl_name, GL_COMPILE_STATUS, &is_compiled_flag);
		return (bool)is_compiled_flag;
	}

	void shader::compile() throw(compile_error){
		const GLchar * chunks[1] = { m_source.c_str() };
		GLint chunk_sizes[1];
		chunk_sizes[0]= m_source.length();

		// Load source
		::glShaderSource(m_gl_name, 1, chunks, chunk_sizes);

		// Compile shader
		::glCompileShader(m_gl_name);

		// Check status
		if (!is_compiled()) {
			throw shader_compile_error(*this);
		}
	}
#if (GLPP_LANG == GLPP_LANG_CXX11) || (GLPP_LANG == GLPP_LANG_CXX0X)
	shared_shader_t open_shader_files(shader_type type, std::initializer_list<const std::string> fnames) {
		std::string source;

		for(const std::string & fname: fnames) {
			std::ifstream shader_file;
			shader_file.open(fname, std::ifstream::in);
			if (!shader_file.is_open())
				throw std::invalid_argument(std::string("Cannot open shader file ") + fname);

			// get length of file:
			shader_file.seekg (0, std::ios::end);
			size_t length = shader_file.tellg();
			shader_file.seekg (0, std::ios::beg);

			// Read all source
			std::string file_source;
			file_source.resize(length);
			shader_file.read(&file_source[0], length);
			source += file_source;
		}

		return shared_shader_t(new shader(type, source));
	}
#endif

	shared_shader_t open_shader_file(shader_type type, const std::string fname) {
		return open_shader_files(type, { fname } );
	}
}
