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
#include "logicop_unit.hpp"
#include "context.hpp"

namespace glpp {

	logicop_unit::logicop_unit(context & ctx)
		:m_ctx(ctx){
	}

	void logicop_unit::enable() {
		::glEnable(GL_COLOR_LOGIC_OP);
	}

	void logicop_unit::disable() {
		::glDisable(GL_COLOR_LOGIC_OP);
	}

	bool logicop_unit::is_enabled() {
		return ::glIsEnabled(GL_COLOR_LOGIC_OP);
	}

	void logicop_unit::set_operand(logic_op op) {
		::glLogicOp(GLPP_CAST_TO_SCALAR(GLenum, op));
	}

	logic_op logicop_unit::get_operand() {
		return GLPP_CAST_TO_SAFE_ENUM(logic_op, m_ctx.get_param_int(context_param_type::LOGIC_OP_MODE));
	}
}
