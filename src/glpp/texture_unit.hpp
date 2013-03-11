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

#ifndef GLPP_TEXTURE_UNIT_HPP_INCLUDED
#define GLPP_TEXTURE_UNIT_HPP_INCLUDED

#include "base.hpp"
#include "texture.hpp"

namespace glpp {

	struct texture_unit_t:
		public named_object<GLenum>,
		public noncopyable{

		friend class context;

		//! Activate this texture unit (deactivate previous one)
		void activate();

		//! Check if this texture unit is the active
		bool is_active() const;

		//! Bind a texture on this unit
		void bind_texture(const texture & tex);

		//! Unbind any texture from a specific target
		void unbind_texture(texture_type tex_type);

		/*void bind_sampler(sampler & sampl);

		void unbind_sampler(texture_type);*/

	protected:

		texture_unit_t(context & ctx, GLenum name);

		context & m_ctx;
	};
}

#endif
