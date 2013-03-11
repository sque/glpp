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

#ifndef GLPP_SCISSOR_TEST_UNIT_HPP_INCLUDED
#define GLPP_SCISSOR_TEST_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that controls scissor testing
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct scissor_test_unit
		:public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Enable scissor testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissor.xml
		 */
		void enable();

		//! Disable scissor testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissor.xml
		 */
		void disable();

		//! Check if scissor testing is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissor.xml
		 */
		bool is_enabled();

		//! Set scissor box for all viewports
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissor.xml
		 */
		void set_box(int x, int y, size_t width, size_t height);

		//! Set scissor box for a viewport
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissorIndexed.xml
		 * @todo Create viewport objecs and use them directly here
		 */
		void set_viewport_box(GLuint vp_id, int x, int y, size_t width, size_t height);

		//! Get currently selected scissor box
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glScissor.xml
		 */
		void get_box(int & x, int & y, size_t & width, size_t & height);

	protected:

		//! Construction is permitted only by glpp::context
		scissor_test_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};
}

#endif
