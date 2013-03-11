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

#ifndef GLPP_LOGICOP_UNIT_HPP_INCLUDED
#define GLPP_LOGICOP_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that controls color logic operation
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct logicop_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Enable color logic operations
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLogicOp.xml
		 */
		void enable();

		//! Disable color logic operations
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLogicOp.xml
		 */
		void disable();

		//! Check if color logic operations are enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLogicOp.xml
		 */
		bool is_enabled();

		//! Set the operand for color logic operations
		/**
		 * This functions does NOT implicitly enable color logic operations.
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLogicOp.xml
		 */
		void set_operand(logic_op op);

		//! Get the the operand for color logic operations
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glLogicOp.xml
		 */
		logic_op get_operand();

	private:

		//! Construction is permitted only by glpp::context
		logicop_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};
}

#endif
