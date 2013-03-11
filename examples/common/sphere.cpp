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
#include "sphere.hpp"
#include <iostream>

sphere::sphere(float radius, size_t segments, size_t rings) {
	float pix2 = (2.0f *M_PI);
	float f_step = M_PI/rings;
	float l_step = pix2/segments;

	//Allocate space
	size_t total_vertices = (rings -1)*segments+2;
	m_vertices.reserve(total_vertices);
	m_vertices.reserve(total_vertices);
	size_t total_trianles = (rings -1)*segments*2;
	m_indices.reserve(total_trianles);

	// Up vertex
	m_vertices.push_back(glm::vec3(0, radius, 0));
	m_normals.push_back(glm::vec3(0, 1, 0));

	// Create middle rings
	for (size_t r = 1; r < rings; r++) {
		float f = f_step * r;
		float pr = sin(f)*radius;
		float y = cos(f)* radius;
		for(size_t s = 0; s < segments; s++) {
			float l = l_step * s;
			glm::vec3 pos(cos(l)*pr, y, sin(l)*pr);
			m_vertices.push_back(pos);
			m_normals.push_back(glm::normalize(pos));
		}
	}

	// Down vertex
	m_vertices.push_back(glm::vec3(0, -radius, 0));
	m_normals.push_back(glm::vec3(0, -1, 0));

	// Create indices

	// Upper cap
	for(size_t s = 0; s < segments; s++) {
		int next_right = (s < segments -1)?1:1 -segments;
		indices_type::value_type pn = s+1;
		m_indices.push_back(pn);
		m_indices.push_back(0);
		m_indices.push_back(pn + next_right);
	}

	// Middle
	for(size_t r = 0; r < rings -2; r++) {
		for(size_t s = 0; s < segments; s++) {
			unsigned int pn = (r * segments) + s +1;
			int next_right = (s < segments -1)?1:1 -segments;

			m_indices.push_back(pn);
			m_indices.push_back(pn + segments + next_right);
			m_indices.push_back(pn + segments);

			m_indices.push_back(pn);
			m_indices.push_back(pn + next_right);
			m_indices.push_back(pn + segments + next_right);
		}
	}

	// Down cap
	indices_type::value_type last_vrt = m_vertices.size()-1;
	for(size_t s = 0; s < segments; s++) {
		indices_type::value_type pn = ((rings-2)*segments) +1 +s;
		int next_right = (s < segments -1)?1:1 -segments;
		m_indices.push_back(pn);
		m_indices.push_back(pn+next_right);
		m_indices.push_back(last_vrt);
	}
}

void sphere::draw() {
	return geometry::draw();
	//return pvao->draw(glpp::primitive_type::POINTS, 0, m_vertices.size());
	::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return mp_vao->draw_elements(m_indices.size(), &m_indices[0]);

	mp_ebo->bind();
	mp_vao->draw_elements(m_indices.size(), (GLuint *)nullptr);
	//geometry::draw();
}
