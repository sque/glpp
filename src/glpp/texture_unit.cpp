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
#include "texture_unit.hpp"
#include "context.hpp"

namespace glpp {

	texture_unit_t::texture_unit_t(context & ctx, GLenum name) :
		m_ctx(ctx){
		m_gl_name = name;
	}

	//! Activate this texture unit (deactivate previous one)
	void texture_unit_t::activate() {
		glActiveTexture(object_name());
	}

	//! Check if this texture unit is active
	bool texture_unit_t::is_active() const {
		return m_ctx.get_param_int(context_param_type::ACTIVE_TEXTURE) == static_cast<int>(object_name());
	}

	//! Bind a texture on this unit
	void texture_unit_t::bind_texture(const texture & tex) {
		activate();
		tex.bind();
	}

	//! Unbind any texture from a specific target
	void texture_unit_t::unbind_texture(texture_type tex_type) {
		activate();
		glBindTexture(GLPP_CAST_TO_SCALAR(GLenum, tex_type), 0);
	}
}
