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

#ifndef GLPP_BLEND_UNIT_HPP_INCLUDED
#define GLPP_BLEND_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that control blending process
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct blend_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Enable blending mode
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFunc.xml
		 */
		void enable();

		//! Disable blending mode
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFunc.xml
		 */
		void disable();

		//! Check if blending mode is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFunc.xml
		 */
		bool is_enabled();

		//! @{
		//! @todo move them to framebuffer
		void set_write_mask(bool red, bool green, bool blue, bool alpha);

		void set_buffer_write_mask(GLuint buffer_index, bool red, bool green, bool blue, bool alpha);

		void get_write_mask(bool & red, bool & green, bool & blue, bool & alpha);
		//! @}

		//! Specify pixel arithmetic
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFunc.xml
		 */
		void set_func(blend_factor sfactor, blend_factor dfactor);

		//! Specify pixel arithmetic per buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFunc.xml
		 * @todo Make it work directly with framebuffers
		 */
		void set_buffer_func(GLuint buffer_index, blend_factor sfactor, blend_factor dfactor);

		//! Specify pixel arithmetic for RGB and alpha components separately
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFuncSeparate.xml
		 */
		void set_func_components(blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha);

		//! Specify pixel arithmetic for RGB and alpha components separately ( per buffer)
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFuncSeparate.xml
		 * @todo Make it work directly with framebuffers
		 */
		void set_buffer_func_components(GLuint buffer_index, blend_factor srgb, blend_factor drgb, blend_factor salpha, blend_factor dalpha);

		//! Get pixel arithmetic for RGB components
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFuncSeparate.xml
		 */
		void get_func_rgb(blend_factor & sfactor, blend_factor & dfactor);

		//! Get pixel arithmetic for Alpha components
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendFuncSeparate.xml
		 */
		void get_func_alpha(blend_factor & sfactor, blend_factor & dfactor);

		//! Set constant color that is needed by some blend_factor.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendColor.xml
		 */
		void set_const_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		//! Get the constant color that is needed by some blend_factor.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBlendColor.xml
		 */
		void get_const_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a);

		//! Specify the equation used for both the RGB blend equation and the Alpha blend equation
		/**
		 * http://www.opengl.org/sdk/docs/man/xhtml/glBlendEquation.xml
		 */
		void set_equation(blend_equation mode);

		//! Specify the equation used for both the RGB blend equation and the Alpha blend equation (per buffer)
		/**
		 * http://www.opengl.org/sdk/docs/man/xhtml/glBlendEquation.xml
		 * @todo Make it work directly with framebuffers
		 */
		void set_buffer_equation(GLuint buffer_index, blend_equation mode);

		//! Get the equation used for the RGB blend equation.
		/**
		 * http://www.opengl.org/sdk/docs/man/xhtml/glBlendEquation.xml
		 */
		blend_equation get_equation_rgb();

		//! Get the equation used for the Alpha blend equation.
		/**
		 * http://www.opengl.org/sdk/docs/man/xhtml/glBlendEquation.xml
		 */
		blend_equation get_equation_alpha();

	private:

		//! Construction is permitted only by glpp::context
		blend_unit(context & ctx);

		//! Reference to context #include <vector>that this is unit is part of.
		context & m_ctx;
	};
}

#endif
