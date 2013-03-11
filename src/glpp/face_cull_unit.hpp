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

#ifndef GLPP_FACE_CULL_UNIT_HPP_INCLUDED
#define GLPP_FACE_CULL_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that controls face culling
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct face_cull_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Enable face culling
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCullFace.xml
		 */
		void enable();

		//! Disable face culling
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCullFace.xml
		 */
		void disable();

		//! Check if face culling is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCullFace.xml
		 */
		bool is_enabled();

		//! Set which faces will be culled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCullFace.xml
		 */
		void set_culled_face(face_type face);

		//! Get which faces will be culled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glCullFace.xml
		 * @see set_culled_face
		 */
		face_type get_culled_face();

		//! Define the orientation of front faces
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFrontFace.xml
		 */
		void set_frontface_orientation(face_orientation orientation);

		//! Get the orientation of front faces
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glFrontFace.xml
		 * @see set_frontface_orientation
		 */
		face_orientation get_frontface_orientation(face_orientation);

	protected:

		//! Construction is permitted only by glpp::context
		face_cull_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};

}


#endif
