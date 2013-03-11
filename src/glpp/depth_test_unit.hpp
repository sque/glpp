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

#ifndef GLPP_DEPTH_TEST_UNIT_HPP_INCLUDED
#define GLPP_DEPTH_TEST_UNIT_HPP_INCLUDED

#include "base.hpp"

namespace glpp {

	//! Unit that controls depth buffer testing
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct depth_test_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Enable depth buffer testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthFunc.xml
		 */
		void enable();

		//! Disable depth buffer testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthFunc.xml
		 */
		void disable();

		//! Check if depth buffer testing is enabled
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthFunc.xml
		 */
		bool is_enabled();

		//! Enable updating depth buffer after testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthMask.xml
		 */
		void enable_write();

		//! Disable updating depth buffer after testing
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthMask.xml
		 */
		void disable_write();

		//! Check if depth buffer is permitted to be updated
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthMask.xml
		 */
		bool is_write_enabled();

		//! Specify mapping of depth values from normalized device coordinates to window coordinates
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthRange.xml
		 */
		void set_range(GLdouble znear, GLdouble zfar);

		//! Get mapping of depth values from normalized device coordinates to window coordinates
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDepthRange.xml
		 * @see set_range
		 */
		void get_range(GLdouble & znear, GLdouble & zfar);

		//! Specify the clear value for the depth buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glClearDepth.xml
		 */
		void set_clear_value(GLdouble depth);

		//! Get the clear value for the depth buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glClearDepth.xml
		 * @see set_clear_value
		 */
		GLdouble get_clear_value();

		//! Specify the function used for depth buffer comparisons
		/**
		 * www.opengl.org/sdk/docs/man4/xhtml/glDepthFunc.xml
		 */
		void set_compare_func(compare_func func);

		//! Get the function used for depth buffer comparisons
		/**
		 * www.opengl.org/sdk/docs/man4/xhtml/glDepthFunc.xml
		 * @see set_compare_func
		 */
		compare_func get_compare_func();

		//! Set the scale and units used to calculate depth values
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void set_polygon_offset(GLfloat factor, GLfloat units);

		//! Get the scale and units used to calculate depth values
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 * @see set_polygon_offset
		 */
		void get_polygon_offset(GLfloat & factor, GLfloat & units);

		//! Enable depth offset for filled fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void enable_fill_polygon_offset();

		//! Disable depth offset for filled fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void disable_fill_polygon_offset();

		//! Check if depth offset is enabled for filled fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		bool is_fill_polygon_offset_enabled();

		//! Enable depth offset for point fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void enable_point_polygon_offset();

		//! Disable depth offset for point fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void disable_point_polygon_offset();

		//! Check if depth offset is enabled for point fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		bool is_point_polygon_offset_enabled();

		//! Enable depth offset for line fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void enable_line_polygon_offset();

		//! Disable depth offset for line fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		void disable_line_polygon_offset();

		//! Check if depth offset is enabled for line fragments
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glPolygonOffset.xml
		 */
		bool is_line_polygon_offset_enabled();

	protected:

		//! Construction is permitted only by glpp::context
		depth_test_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};
}

#endif
