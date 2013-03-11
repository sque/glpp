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
#include "global_uniform.hpp"
#include "program.hpp"

namespace glpp {

	global_uniform::global_uniform(program * pprog, const std::string & name, name_type uni_index, location_type location) :
		uniform(pprog, name, uni_index),
		m_gl_location(location) {
	}

	void global_uniform::set1f(GLfloat v1) {
		::glProgramUniform1f(mp_program->object_name(), location(),v1);
	}

	void global_uniform::set2f(GLfloat v1, GLfloat v2) {
		::glProgramUniform2f(mp_program->object_name(), location(), v1, v2);
	}

	void global_uniform::set2f(const GLfloat * pv, size_t count) {
		::glProgramUniform2fv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set3f(GLfloat v1, GLfloat v2, GLfloat v3) {
		::glProgramUniform3f(mp_program->object_name(), location(), v1, v2 ,v3);
	}

	void global_uniform::set3f(const GLfloat * pv, size_t count) {
		::glProgramUniform3fv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set4f(GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
		::glProgramUniform4f(mp_program->object_name(), location(), v1, v2, v3 ,v4);
	}

	void global_uniform::set4f(const GLfloat * pv, size_t count) {
		::glProgramUniform4fv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set1d(GLdouble v1) {
		::glProgramUniform1d(mp_program->object_name(), location(), v1);
	}

	void global_uniform::set2d(GLdouble v1, GLdouble v2) {
		::glProgramUniform2d(mp_program->object_name(), location(), v1, v2);
	}

	void global_uniform::set2d(const GLdouble * pv, size_t count) {
		::glProgramUniform2dv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set3d(GLdouble v1, GLdouble v2, GLdouble v3) {
		::glProgramUniform3d(mp_program->object_name(), location(), v1, v2, v3);
	}

	void global_uniform::set3d(const GLdouble * pv, size_t count) {
		::glProgramUniform3dv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set4d(GLdouble v1, GLdouble v2, GLdouble v3, GLdouble v4) {
		::glProgramUniform4d(mp_program->object_name(), location(), v1, v2, v3, v4);
	}

	void global_uniform::set4d(const GLdouble * pv, size_t count) {
		::glProgramUniform4dv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set1i(GLint v1) {
		::glProgramUniform1i(mp_program->object_name(), location(), v1);
	}

	void global_uniform::set2i(GLint v1, GLint v2) {
		::glProgramUniform2i(mp_program->object_name(), location(), v1, v2);
	}

	void global_uniform::set2i(const GLint * pv, size_t count) {
		::glProgramUniform2iv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set3i(GLint v1, GLint v2, GLint v3) {
		::glProgramUniform3i(mp_program->object_name(), location(), v1, v2, v3);
	}

	void global_uniform::set3i(const GLint * pv, size_t count) {
		::glProgramUniform3iv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set4i(GLint v1, GLint v2, GLint v3, GLint v4) {
		::glProgramUniform4i(mp_program->object_name(), location(), v1, v2, v3, v4);
	}

	void global_uniform::set4i(const GLint * pv, size_t count) {
		::glProgramUniform4iv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set1ui(GLuint v1) {
		::glProgramUniform1ui(mp_program->object_name(), location(), v1);
	}

	void global_uniform::set2ui(GLuint v1, GLuint v2) {
		::glProgramUniform2ui(mp_program->object_name(), location(), v1, v2);
	}

	void global_uniform::set2ui(const GLuint * pv, size_t count) {
		::glProgramUniform2uiv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set3ui(GLuint v1, GLuint v2, GLuint v3) {
		::glProgramUniform3ui(mp_program->object_name(), location(), v1, v2, v3);
	}

	void global_uniform::set3ui(const GLuint * pv, size_t count) {
		::glProgramUniform3uiv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::set4ui(GLuint v1, GLuint v2, GLuint v3, GLuint v4) {
		::glProgramUniform4ui(mp_program->object_name(), location(), v1, v2, v3, v4);
	}

	void global_uniform::set4ui(const GLuint * pv, size_t count) {
		::glProgramUniform4uiv(mp_program->object_name(), location(), count, pv);
	}

	void global_uniform::setmat2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat2x3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x3fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat2x4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x4fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3x2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x2fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3x4f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x4fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}
	void global_uniform::setmat4x2f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x2fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat4x3f(const GLfloat *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x3fv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat2x3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x3dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat2x4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix2x4dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3x2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x2dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat3x4d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix3x4dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat4x2d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x2dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

	void global_uniform::setmat4x3d(const GLdouble *pm, bool transpose, size_t count) {
		::glProgramUniformMatrix4x3dv(mp_program->object_name(), location(), count,
				(GLboolean) transpose, pm);
	}

}
