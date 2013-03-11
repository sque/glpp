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
#include "effect.hpp"
#include <boost/format.hpp>
#include <stdio.h>

bool file_exists(const std::string  & filename) {
	if (FILE * file = fopen(filename.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	return false;
}

effect_pass::effect_pass(const std::string & name, const std::string & shaders_folder):
	m_name(name),
	m_shaders_folder(shaders_folder){

	if (has_vertex_shader()) {
		if (has_common_header())
			mp_vert_shader = glpp::open_shader_files(glpp::shader_type::VERTEX, {common_shader_file(), vertex_shader_file()});
		else
			mp_vert_shader = glpp::open_shader_file(glpp::shader_type::VERTEX, vertex_shader_file());
	}

	if (has_fragment_shader()){
		if (has_common_header())
			mp_frag_shader = glpp::open_shader_files(glpp::shader_type::FRAGMENT, {common_shader_file(), fragment_shader_file()});
		else
			mp_frag_shader = glpp::open_shader_file(glpp::shader_type::FRAGMENT, fragment_shader_file());
	}
}

std::string effect_pass::vertex_shader_file() const {
	return m_shaders_folder + std::string("/") + m_name + std::string(".vert");
}

std::string effect_pass::fragment_shader_file() const {
	return m_shaders_folder + std::string("/") + m_name + std::string(".frag");
}

std::string effect_pass::common_shader_file() const {
	return m_shaders_folder + std::string("/") + m_name + std::string(".hsh");
}

bool effect_pass::has_common_header() {
	return file_exists(common_shader_file());
}

bool effect_pass::has_vertex_shader() {
	return file_exists(vertex_shader_file());
}

bool effect_pass::has_fragment_shader() {
	return file_exists(fragment_shader_file());
}

effect::effect(const std::initializer_list<const std::string> & passes, const std::string & shaders_folder) :
	m_shaders_folder(shaders_folder),
	m_built(){

	for(auto pass : passes) {
		m_passes.push_back(effect_pass(pass, m_shaders_folder));
	}
}

void effect::build() {
	if (m_built)
		return;

	// Create main loops
	std::string main_vert, main_frag;

	main_vert = main_frag = "#version 420\n";
	for(auto pass: m_passes) {
		main_vert += (boost::format("void %1%(void);\n") % pass.name()).str();
		main_frag += (boost::format("void %1%(void);\n") % pass.name()).str();
	}

	main_vert += "void main(void){\n";
	main_frag += "void main(void){\n";

	for(auto pass: m_passes) {
		if (pass.has_vertex_shader()) {
			main_vert += (boost::format("  %1%();\n") % pass.name()).str();
			m_program.attach_shader(pass.mp_vert_shader);
		}

		if (pass.has_fragment_shader()) {
			main_frag += (boost::format("  %1%();\n") % pass.name()).str();
			m_program.attach_shader(pass.mp_frag_shader);
		}
	}
	main_vert += "}\n";
	main_frag += "}\n";

	printf("vertex main:\n%s", main_vert.c_str());
	printf("fragment main:\n%s", main_frag.c_str());

	m_program.attach_shader(glpp::shared_shader_t(new glpp::shader(glpp::shader_type::VERTEX, main_vert)));
	m_program.attach_shader(glpp::shared_shader_t(new glpp::shader(glpp::shader_type::FRAGMENT, main_frag)));

	m_program.build();
}
