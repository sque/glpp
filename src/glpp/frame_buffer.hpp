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

#ifndef GLPP_FRAME_BUFFER_HPP_INCLUDED
#define GLPP_FRAME_BUFFER_HPP_INCLUDED

#include "base.hpp"
#include "render_buffer.hpp"
#include "texture.hpp"
#include <map>

namespace glpp {

	//! Attachment point of a @ref frame_buffer object
	/**
	 * This interface permits to query and manage an attachment
	 * point of a frame_buffer object
	 * @remarks non-copyable, non-inheritable, RAII
	 */
	struct frame_buffer_attachment_point :
		public noncopyable{

		//! All attachment points belong and are managed by a @ref frame_buffer object.
		friend class frame_buffer;

		//! Attach a @ref texture as a logical buffer to the frame_buffer object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFramebufferTexture.xml
		 */
		void attach(shared_texture_t & ptex, int level);

		//! Attach a 2D @ref texture as a logical buffer to the framebuffer object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFramebufferTexture.xml
		 */
		void attach(shared_texture_t & ptex, int level, tex2d_update_target tex_target, int layer);

		//! Attach a @ref render_buffer as a logical buffer to the frame_buffer object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFramebufferRenderbuffer.xml
		 */
		void attach(shared_render_buffer_t prbo);

		//! Detach any logical buffer from this attachment point
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFramebufferRenderbuffer.xml
		 */
		void detach();

		//! Get @ref frame_buffer that this attachment_point belongs to.
		const frame_buffer & owner_frame_buffer() const {
			return *mp_fbo;
		}

		//! Get the actual point that this object manages
		fbo_point point() const {
			return m_point;
		}

		//! Read pixels from this buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glReadPixels.xml
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glReadBuffer.xml
		 */
		void read_pixels(int x, int y, size_t width, size_t height, pixel_data_format format, fbo_pixel_type pix_type, void * dst) const;

	protected:

		//! Constructor is only called by @ref frame_buffer owner
		frame_buffer_attachment_point(const frame_buffer * pfbo, fbo_point point);

		//! Pointer to owner object of this point
		const frame_buffer * mp_fbo;

		//! Actual point of this attachment
		fbo_point m_point;
	};

	//! Object representing a framebuffer
	/**
	 * Framebuffer Objects are a mechanism for rendering to images
	 * other than the default OpenGL Default Framebuffer
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_buffer
	 */
	struct frame_buffer :
		public named_object<GLuint>,
		public noncopyable{

		//! Create an empty framebuffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGenFramebuffers.xml
		 */
		frame_buffer(frame_buffer_target target = frame_buffer_target::DRAW);

		//! Delete this framebuffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDeleteFramebuffers.xml
		 */
		~frame_buffer();

		//! Bind as framebuffer on its defined target
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBindFramebuffer.xml
		 */
		void bind() const;

		//! Get target of this frame buffer
		inline frame_buffer_target target() const {
			return m_target;
		}

		//! Get current window default framebuffer
		/**
		 * Every window initializes a default framebuffer.
		 */
		static const frame_buffer & window_default();

		//! Get status of this framebuffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCheckFramebufferStatus.xml
		 */
		frame_buffer_status status() const;

		//! Check if this framebuffer is complete
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCheckFramebufferStatus.xml
		 * @see status()
		 */
		bool is_complete() const {
			return (status() == frame_buffer_status::COMPLETE);
		}

		//! Access properties object of an attachment point
		shared_frame_buffer_attachment_point_t point(fbo_point point);

	protected:

		//! Type of attachment points container
		typedef std::map<fbo_point, shared_frame_buffer_attachment_point_t> points_container_type;

		//! Container of all attachment points
		points_container_type m_points;

		//! Target of this frame_buffer
		frame_buffer_target m_target;

		//! Static pointer to window default fbo
		static frame_buffer * ms_window_fbo;

		//! Private constructor for binding on already cretead FBO
		frame_buffer(name_type name, frame_buffer_target target);

	};
}


#endif
