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

#ifndef GLPP_BASE_HPP_INCLUDED
#define GLPP_BASE_HPP_INCLUDED

#include "setup.hpp"
#include "types.hpp"
#include "exception.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <memory>

//! The namespace that encloses everything of GLPP
namespace glpp {

	//! Base type for OpenGL objects
	/**
	 * All OpenGL objects are described by a constant name (handle).
	 * This is the base class that exposes the name (handle) of the object.
	 * http://www.opengl.org/wiki/OpenGL_Objects
	 */
	template <class NameType>
	class named_object {
	public:

		//! Type of the name
		/**
		 * Not all objects use the same type for name.
		 */
		typedef NameType name_type;

		//! Return the name of object (handle)
		/**
		 * The name can be used directly by OpenGL functions.
		 */
		inline name_type object_name() const {
			return  m_gl_name;
		}

	protected:
		//! Stored object name
		NameType m_gl_name;
	};

	// Forward declaration of data types
	class context;
	class shader;
	class program;
	class uniform;
	class uniform_block;
	class global_uniform;
	class frame_buffer;
	class render_buffer;
	class buffer;
	class texture;
	class vertex_array;
	class vertex_attrib_array;
	class frame_buffer_attachment_point;


	//! Type definition of shared pointer for @ref shader objects
	typedef GLPP_SHARED_PTR(shader) shared_shader_t;

	//! Type definition of shared pointer for @ref uniform objects
	typedef GLPP_SHARED_PTR( uniform ) shared_uniform_t;

	//!Type definition of shared pointer for @ref uniform_block objects
	typedef GLPP_SHARED_PTR( uniform_block ) shared_uniform_block_t;

	//!Type definition of shared pointer for @ref global_uniform objects
	typedef GLPP_SHARED_PTR( global_uniform ) shared_global_uniform_t;

	//!Type definition of shared pointer for @ref vertex_attrib_array objects
	typedef GLPP_SHARED_PTR( vertex_attrib_array ) shared_vertex_attrib_array_t;

	//!Type definition of shared pointer for @ref render_buffer objects
	typedef GLPP_SHARED_PTR( render_buffer ) shared_render_buffer_t;

	//!Type definition of shared pointer for @ref texture objects
	typedef GLPP_SHARED_PTR( texture ) shared_texture_t;

	//!Type definition of shared pointer for @ref frame_buffer_attachment_point objects
	typedef GLPP_SHARED_PTR( frame_buffer_attachment_point ) shared_frame_buffer_attachment_point_t;

	template<class R, class T, class N, class E>
	R gl_get_wrapper(void (*f)(N, GLenum, T *), N i, E pname) {
		T v;
		f(i, static_cast<GLenum>(pname), &v);
		return R(v);
	}

	template<class T, class N, class E>
	T gl_get_wrapper(void (*f)(N, GLenum, T *), N i, E pname) {
		T v;
		f(i, GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}


	/**
	 * @defgroup context_unit Context Units
	 * @{
	 * @brief Units that can control parts of the pipeline process.
	 *
	 * Pipeline is divided in some logical units that are responsible for specific
	 * set of operations. In GLpp these units are represented in their own classes
	 * and they wrap all functions that are need to control this part of pipeline. To
	 * access a unit you need to ask the relevant object from the glpp::context instance.
	 * @}
	 */

	/**
	 * @defgroup gpu_program GPU Programmable pipeline
	 * @{
	 * @brief Manage GPU programs in the pipeline.
	 *
	 * In OpenGL many parts of pipeline are dynamically programmable by user. This module
	 * wraps all parts of OpenGL that are directly responsible for manipulating user programs.
	 * @}
	 *
	 */

	/**
	 * @defgroup gpu_buffer GPU Buffers
	 * @{
	 * @brief Manage in-GPU buffers.
	 *
	 * OpenGL uses various buffers. Each one is optimized for a specific usage.
	 * @}
	 *
	 */

	/**
	 * @page exclusive_glpp_api Function depends on using only GLPP API
	 * Some functions of the GLPP API to work properly, depend on the fact that there
	 * is no direct use of OpenGL API.
	 *
	 * The functions that are marked like this, usually have more info about which
	 * functions of the GLPP API must not be bypassed by using direct OpenGL API.
	 */
}

#endif
