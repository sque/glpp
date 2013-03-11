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

#ifndef TESTS_EFFECT_HPP_
#define TESTS_EFFECT_HPP_

#include "internal.hpp"
#include <initializer_list>

class effect_pass {
public:

	effect_pass(const std::string & name, const std::string & shaders_folder = ".");

	std::string vertex_shader_file() const;

	std::string fragment_shader_file() const;

	std::string common_shader_file() const;

	bool has_common_header();

	bool has_vertex_shader();

	bool has_fragment_shader();

	std::string & name() {
		return m_name;
	}

	std::string m_name;

	std::string m_shaders_folder;

	glpp::shared_shader_t mp_vert_shader;

	glpp::shared_shader_t mp_frag_shader;
};

class effect{
public:

	effect(const std::initializer_list<const std::string> & passes, const std::string & shaders_folder = "effects");

	glpp::program & get_program(){
		return m_program;
	}

	void build();

	bool is_built() const {
		return m_built;
	}
protected:

	std::string m_shaders_folder;

	typedef std::vector<effect_pass> passes_type;

	passes_type m_passes;

	glpp::program m_program;

	bool m_built;


};

#endif
