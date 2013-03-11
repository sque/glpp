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

#ifndef GLPP_CONTEXT_HPP_INCLUDED
#define GLPP_CONTEXT_HPP_INCLUDED

#include <vector>
#include "base.hpp"
#include "exception.hpp"
#include "depth_test_unit.hpp"
#include "stencil_test_unit.hpp"
#include "scissor_test_unit.hpp"
#include "face_cull_unit.hpp"
#include "blend_unit.hpp"
#include "logicop_unit.hpp"
#include "capabilities_unit.hpp"
#include "texture_unit.hpp"

namespace glpp {

	//! Opengl Context
	struct context {

		//! Create a new GLPP context for current thread
		static bool create();

		GLint get_param_int(context_param_type pname) const;

		GLuint get_param_uint(context_param_type pname) const {
			return (GLuint)get_param_int64(pname);
		}

		GLint64 get_param_int64(context_param_type pname) const;

		bool get_param_bool(context_param_type pname) const;

		GLfloat get_param_float(context_param_type pname) const;

		GLdouble get_param_double(context_param_type pname) const;

		std::vector<int> get_param_intv(context_param_type pname, size_t size);

		std::vector<GLint64> get_param_int64v(context_param_type pname, size_t size);

		std::vector<float> get_param_floatv(context_param_type pname, size_t size);

		std::vector<double> get_param_doublev(context_param_type pname, size_t size);


		//! Access depth test unit of this context
		inline depth_test_unit & depth_test() {
			return m_depth_test;
		}

		//! Access stencil test unit of this context
		inline stencil_test_unit & stencil_test() {
			return m_stencil_test;
		}

		//! Access scissor test unit of this context
		inline scissor_test_unit & scissor_test() {
			return m_scissor_test;
		}

		//! Access blend unit of this context
		inline blend_unit & blend() {
			return m_blend_unit;
		}

		//! Access color logical operations unit of this context
		inline logicop_unit & logicop() {
			return m_logicop_unit;
		}

		//! Access face cull unit of this context
		inline face_cull_unit & face_cull() {
			return m_face_cull;
		}

		//! Access a specific texture_unit
		texture_unit_t & texture_unit(size_t index);

		//! Get the index of the active texture unit
		size_t active_texture_unit() const;

		//! Access the capabilities query interface
		capabilities_unit & capabilities() {
			return m_capabilities;
		}

		//! Destructor
		~context();
	protected:

		//! Depth test unit
		depth_test_unit m_depth_test;

		//! Stencil test unit
		stencil_test_unit m_stencil_test;

		//! Scissor test unit
		scissor_test_unit m_scissor_test;

		//! Blend unit
		blend_unit m_blend_unit;

		//! Logicop unit
		logicop_unit m_logicop_unit;

		//! Query capabilities interface
		capabilities_unit m_capabilities;

		//! Face cull unit
		face_cull_unit m_face_cull;

		//! Texture unit collection
		typedef std::vector<texture_unit_t *> texture_unit_collection;

		//! Texture units collection
		texture_unit_collection m_texture_units;

	private:
		//! Context is only constructed indirectly by static API
		/**
		 * see create()
		 */
		context();
	};

	//! Get the current context for this thread.
	/**
	 * You need to manually context::create() for each context that you need.
	 * @throw no_active_context If there is no active context
	 */
	context & current_ctx() throw(no_active_context);
}

#endif
