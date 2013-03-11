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

#ifndef GLPP_GLOBAL_UNIFORM_HPP_INCLUDED
#define GLPP_GLOBAL_UNIFORM_HPP_INCLUDED

#include "base.hpp"
#include "uniform.hpp"

namespace glpp {

	//! Active uniform variable of global scope
	/**
	 * Uniforms that do not belong to any @ref uniform_block, belong to global scope.
	 * These variable values must be set manually, one by one.
	 * @remarks non-copyable, non-inheritable, RAII
	 * @ingroup gpu_program
	 * @see program::get_uniform(), program::get_global_uniform()
	 */
	struct global_uniform :
		public uniform {

		//! All uniforms belong and are managed by a @ref program object.
		friend class program;

		//! Type of uniform location
		typedef GLint location_type;

		//! Get unique location of this variable in global uniform block
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetUniformLocation.xml
		 */
		location_type location() const {
			return m_gl_location;
		}

		/**
		 * @{
		 * @name glUniform like functions
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glUniform.xml
		 */
		void set1f(GLfloat v1);
		void set2f(GLfloat v1, GLfloat v2);
		void set2f(const GLfloat * pv, size_t count = 1);
		void set3f(GLfloat v1, GLfloat v2, GLfloat v3);
		void set3f(const GLfloat * pv, size_t count = 1);
		void set4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
		void set4f(const GLfloat * pv, size_t count = 1);

		void set1d(GLdouble v1);
		void set2d(GLdouble v1, GLdouble v2);
		void set2d(const GLdouble * pv, size_t count = 1);
		void set3d(GLdouble v1, GLdouble v2, GLdouble v3);
		void set3d(const GLdouble * pv, size_t count = 1);
		void set4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4);
		void set4d(const GLdouble * pv, size_t count = 1);

		void set1i(GLint v1);
		void set2i(GLint v1, GLint v2);
		void set2i(const GLint * pv, size_t count = 1);
		void set3i(GLint v1, GLint v2, GLint v3);
		void set3i(const GLint * pv, size_t count = 1);
		void set4i(GLint v1, GLint v2, GLint v3, GLint v4);
		void set4i(const GLint * pv, size_t count = 1);

		void set1ui(GLuint v1);
		void set2ui(GLuint v1, GLuint v2);
		void set2ui(const GLuint * pv, size_t count = 1);
		void set3ui(GLuint v1, GLuint v2, GLuint v3);
		void set3ui(const GLuint * pv, size_t count = 1);
		void set4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4);
		void set4ui(const GLuint * pv, size_t count = 1);

		void setmat2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat2x3f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat2x4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3x2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat3x4f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4x2f(const GLfloat *pm, bool transpose = false, size_t count = 1);
		void setmat4x3f(const GLfloat *pm, bool transpose = false, size_t count = 1);

		void setmat2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat2x3d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat2x4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3x2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat3x4d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4x2d(const GLdouble *pm, bool transpose = false, size_t count = 1);
		void setmat4x3d(const GLdouble *pm, bool transpose = false, size_t count = 1);

		//! @}

	protected:

		//! Location of uniform variable in global block
		location_type m_gl_location;

		//! Constructed only by program.
		global_uniform(program * pprog, const std::string & name, name_type uni_index, location_type location);
	};
}
#endif
