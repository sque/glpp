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

#ifndef GLPP_STENCIL_TEST_UNIT_HPP_INCLUDED
#define GLPP_STENCIL_TEST_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that controls stencil testing
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct stencil_test_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Type of user defined binary mask for stencil operations
		/**
		 * @see set_write_mask, set_compare_func
		 */
		typedef GLuint mask_type;

		//! Type of reference value that used in comparison at stencil test operation
		/**
		 * @see set_write_mask, set_compare_func
		 */
		typedef GLint compare_reference_type;

		//! Enable stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFunc.xml
		 */
		void enable();

		//! Disable stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFunc.xml
		 */
		void disable();

		//! Check if stencil testing is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFunc.xml
		 */
		bool is_enabled();

		//! Control the front and back writing of individual bits in the stencil planes
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilMask.xml
		 */
		void set_write_mask(mask_type mask);

		//! Control the front and/or back writing of individual bits in the stencil planes
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilMaskSeparate.xml
		 */
		void set_face_write_mask(face_type face, mask_type mask);

		//! Get the current write mask that is used for writing front-facing polygons.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilMaskSeparate.xml
		 */
		mask_type get_write_mask();

		//! Get the current write mask that is used for writing back-facing polygons.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilMaskSeparate.xml
		 */
		mask_type get_back_write_mask();

		//! Set front and back function and reference value for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFunc.xml
		 */
		void set_compare_func(compare_func func, compare_reference_type ref, mask_type mask);

		//! Set front and/or back function and reference value for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 */
		void set_face_compare_func(face_type face, compare_func func, compare_reference_type ref, mask_type mask);

		//! Get front function for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 */
		compare_func get_compare_func();

		//! Get back function for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 * @see set_compare_func, set_face_compare_func
		 */
		compare_func get_back_compare_func();

		//! Get back compare mask for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 * @see set_compare_func, set_face_compare_func
		 */
		mask_type get_compare_mask();

		//! Get front compare mask for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 * @see set_compare_func, set_face_compare_func
		 */
		mask_type get_back_compare_mask();

		//! Get front compare reference for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 * @see set_compare_func, set_face_compare_func
		 */
		compare_reference_type get_compare_reference();

		//! Get back compare reference for stencil testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilFuncSeparate.xml
		 * @see set_compare_func, set_face_compare_func
		 */
		compare_reference_type get_back_compare_reference();

		//! Set front and back stencil test actions
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOp.xml
		 */
		void set_op(stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass);

		//! Set front and/or back stencil test actions
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 */
		void set_face_op(face_type face, stencil_op stencil_fail, stencil_op stencil_pass_depth_fail, stencil_op stencil_pass_depth_pass);

		//! Get action taken when front stencil test failed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_stencil_fail_op();

		//! Get action taken when back stencil test failed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_back_stencil_fail_op();

		//! Get action taken when front stencil passed and depth test failed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_stencil_pass_depth_fail_op();

		//! Get action taken when back stencil passed and depth test failed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_back_stencil_pass_depth_fail_op();

		//! Get action taken when both front stencil and depth test passed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_stencil_pass_depth_pass_op();

		//! Get action taken when both back stencil and depth test passed
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_back_stencil_pass_depth_pass_op();

		//! Get action taken based on the case described by parameter
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glStencilOpSeparate.xml
		 * @see set_op, set_face_op
		 */
		stencil_op get_op(face_type face, bool stencil_pass, bool depth_pass) throw(std::invalid_argument);

	protected:

		//! Construction is permitted only by glpp::context
		stencil_test_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};
}


#endif
