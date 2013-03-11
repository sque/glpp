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
#include "scissor_test_unit.hpp"
#include "context.hpp"

namespace glpp {

	scissor_test_unit::scissor_test_unit(context & ctx) :
		m_ctx(ctx){
	}

	void scissor_test_unit::enable() {
		::glEnable(GL_SCISSOR_TEST);
	}

	void scissor_test_unit::disable() {
		::glDisable(GL_SCISSOR_TEST);
	}

	bool scissor_test_unit::is_enabled() {
		return ::glIsEnabled(GL_SCISSOR_TEST);
	}

	void scissor_test_unit::set_box(int x, int y, size_t width, size_t height) {
		::glScissor(x, y, width, height);
	}

	void scissor_test_unit::set_viewport_box(GLuint vp_id, int x, int y, size_t width, size_t height) {
		::glScissorIndexed(vp_id, x, y, width, height);
	}

	void scissor_test_unit::get_box(int & x, int & y, size_t & width, size_t & height) {
		std::vector<int> box = m_ctx.get_param_intv(context_param_type::SCISSOR_BOX, 4);
		x = box[0];
		y = box[1];
		width = box[2];
		height = box[3];
	}

}
