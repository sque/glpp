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
#include "skybox.hpp"

skybox::skybox(float size, const std::string & imgfname, std::initializer_list<const std::string> vert_shaders, std::initializer_list<const std::string> frag_shaders):
	cube(size),
	m_img_fname(imgfname){

	for(const std::string & sh : frag_shaders) {
		m_frag_shaders.push_back(sh);
	}

	for(const std::string & sh : vert_shaders) {
		m_vert_shaders.push_back(sh);
	}

	m_indices.clear();
	m_indices = { 2, 0, 1,
			3, 0, 2,
			0, 4, 1,
			1, 4, 5,
			2, 6, 3,
			3, 6, 7,
			4, 6, 5,
			4, 7, 6,
			0, 3, 4,
			3, 7, 4,
			1, 5, 2,
			2, 5, 6
	};
}

skybox::~skybox(){}


void skybox::draw() {
	bool was_enabled = glpp::current_ctx().depth_test().is_enabled();
	glpp::current_ctx().depth_test().disable();
	cube::draw();
	if (was_enabled)
		glpp::current_ctx().depth_test().enable();
}

void skybox::create_globjects() {
	cube::create_globjects();

	mp_tex = new glpp::texture(glpp::texture_type::TEX_CUBEMAP);
	load_texturecube_from_file(mp_tex, m_img_fname, true);

	glpp::assert_no_glerror("Cannot parameterize cube map.");

	if (m_frag_shaders.size() && m_vert_shaders.size()) {
		mp_prog = new glpp::program();
		for(const std::string & vsh : m_vert_shaders)
			mp_prog->attach_shader(glpp::open_shader_file(glpp::shader_type::VERTEX, {vsh}));
		for(const std::string & fsh : m_frag_shaders)
			mp_prog->attach_shader(glpp::open_shader_file(glpp::shader_type::FRAGMENT, {fsh}));
		mp_prog->build();

		mp_prog->get_global_uniform("skyCubeMap")->set1i(12);	// 4th texture unit has map
	}

	glpp::current_ctx().texture_unit(12).bind_texture(*mp_tex);
}
