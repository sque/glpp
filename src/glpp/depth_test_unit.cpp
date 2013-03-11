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
#include "depth_test_unit.hpp"
#include "context.hpp"

namespace glpp {

	depth_test_unit::depth_test_unit(context & ctx):
		m_ctx(ctx){
	}

	void depth_test_unit::get_range(GLdouble & znear, GLdouble & zfar) {
		std::vector<double> res = m_ctx.get_param_doublev(context_param_type::DEPTH_RANGE, 2);
		znear = res[0];
		zfar = res[1];
		return;
	}

	void depth_test_unit::set_range(GLdouble znear, GLdouble zfar) {
		::glDepthRange(znear, zfar);
	}

	void depth_test_unit::enable() {
		::glEnable(GL_DEPTH_TEST);
	}

	void depth_test_unit::disable() {
		::glDisable(GL_DEPTH_TEST);
	}

	bool depth_test_unit::is_enabled() {
		return m_ctx.get_param_bool(context_param_type::DEPTH_TEST);
	}

	void depth_test_unit::set_clear_value(GLdouble depth) {
		::glClearDepth(depth);
	}

	GLdouble depth_test_unit::get_clear_value() {
		return m_ctx.get_param_double(context_param_type::DEPTH_CLEAR_VALUE);
	}

	void depth_test_unit::enable_write() {
		::glEnable(GL_DEPTH_WRITEMASK);
	}

	void depth_test_unit::disable_write() {
		::glDisable(GL_DEPTH_WRITEMASK);
	}

	bool depth_test_unit::is_write_enabled() {
		return m_ctx.get_param_bool(context_param_type::DEPTH_WRITEMASK);
	}

	compare_func depth_test_unit::get_compare_func() {
		return GLPP_CAST_TO_SAFE_ENUM(compare_func, m_ctx.get_param_int(context_param_type::DEPTH_FUNC));
	}

	void depth_test_unit::set_compare_func(compare_func func) {
		::glDepthFunc(GLPP_CAST_TO_SCALAR(GLenum, func));
	}

	void depth_test_unit::get_polygon_offset(GLfloat & factor, GLfloat & units) {
		factor = m_ctx.get_param_float(context_param_type::POLYGON_OFFSET_FACTOR);
		units = m_ctx.get_param_float(context_param_type::POLYGON_OFFSET_UNITS);
	}

	void depth_test_unit::set_polygon_offset(GLfloat factor, GLfloat units) {
		::glPolygonOffset(factor, units);
	}

	void depth_test_unit::enable_fill_polygon_offset() {
		::glEnable(GL_POLYGON_OFFSET_FILL);
	}

	void depth_test_unit::disable_fill_polygon_offset() {
		::glDisable(GL_POLYGON_OFFSET_FILL);
	}

	bool depth_test_unit::is_fill_polygon_offset_enabled() {
		return ::glIsEnabled(GL_POLYGON_OFFSET_FILL);
	}

	void depth_test_unit::enable_point_polygon_offset() {
		::glEnable(GL_POLYGON_OFFSET_POINT);
	}

	void depth_test_unit::disable_point_polygon_offset() {
		::glDisable(GL_POLYGON_OFFSET_POINT);
	}

	bool depth_test_unit::is_point_polygon_offset_enabled() {
		return ::glIsEnabled(GL_POLYGON_OFFSET_POINT);
	}

	void depth_test_unit::enable_line_polygon_offset() {
		::glEnable(GL_POLYGON_OFFSET_LINE);
	}

	void depth_test_unit::disable_line_polygon_offset() {
		::glDisable(GL_POLYGON_OFFSET_LINE);
	}

	bool depth_test_unit::is_line_polygon_offset_enabled() {
		return ::glIsEnabled(GL_POLYGON_OFFSET_LINE);
	}

}
