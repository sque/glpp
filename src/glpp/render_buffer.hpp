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

#ifndef GLPP_RENDER_BUFFER_HPP_INCLUDED
#define GLPP_RENDER_BUFFER_HPP_INCLUDED

#include "base.hpp"
#include "exception.hpp"

namespace glpp {

	//! Buffer that can be attached to a @ref frame_buffer as an output target.
	/**
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_buffer
	 */
	struct render_buffer :
		public named_object<GLuint>,
		public noncopyable {

		//! Construct an empty render buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGenRenderbuffers.xml
		 */
		render_buffer();

		//! Construct and define storage
		/**
		 * @see render_buffer(), define_storage()
		 */
		render_buffer(image_rendable_format internal_format, size_t width, size_t height, size_t samples = 0) throw(gl_error);

		//! Destroy and release resources
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDeleteRenderbuffers.xml
		 */
		~render_buffer();

		//! Bind this object to active render buffer target
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBindRenderbuffer.xml
		 */
		void bind();

		//! Establish data storage, format, dimensions and sample count of a renderbuffer object's image
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glRenderbufferStorageMultisample.xml
		 */
		void define_storage(image_rendable_format internal_format, size_t width, size_t height, size_t samples = 0) throw(gl_error);
	};
}

#endif
