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

#ifndef GLPP_TESTS_MOUSE_DRAG_HPP_INCLUDED
#define GLPP_TESTS_MOUSE_DRAG_HPP_INCLUDED

#include <glm/glm.hpp>
class mouse_drag {
public:

	mouse_drag():
		m_dragging(false){
	}

	void start_dragging(int x, int y) {
		m_last_pos.x = x;
		m_last_pos.y = y;
		m_dragging = true;
	}

	void stop_dragging() {
		m_dragging = false;
	}

	bool is_dragging() {
		return m_dragging;
	}

	glm::vec2 get_drag(int x, int y) {
		if (!m_dragging)
			return glm::vec2(0,0);

		glm::vec2 trans = m_last_pos - glm::vec2(x, y);
		m_last_pos = glm::vec2(x, y);
		return trans;
	}

protected:
	glm::vec2 m_last_pos;

	bool m_dragging;
};

#endif
