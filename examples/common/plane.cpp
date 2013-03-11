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
#include "plane.hpp"

plane::plane(const glm::vec3 & side, const glm::vec3 & normal, float size, float tile_size):
	m_side(side),
	m_normal(normal),
	m_size(size){

	m_side = glm::normalize(m_side);
	m_normal = glm::normalize(normal);
	m_other_side = glm::normalize(glm::cross(m_side, m_normal));

	glm::vec3 hs_side = m_side * size * 0.5f;
	glm::vec3 hs_other_side = m_other_side * size * 0.5f;

	m_vertices.push_back(hs_other_side + hs_side);
	m_vertices.push_back(hs_other_side - hs_side);
	m_vertices.push_back(-hs_other_side - hs_side);
	m_vertices.push_back(-hs_other_side + hs_side);

	float tiles = size/tile_size;
	m_texcoords.push_back(glm::vec3(tiles, tiles, 0));
	m_texcoords.push_back(glm::vec3(tiles, 0, 0));
	m_texcoords.push_back(glm::vec3(0, 0, 0));
	m_texcoords.push_back(glm::vec3(0, tiles, 0));

	for(int i =0 ;i < 4;i++) {
		m_normals.push_back(normal);
		m_tangents.push_back(m_side);
		m_bitangents.push_back(m_other_side);
	}

	for(int i =0 ;i < 4;i++)
		m_vertices.push_back(normal);



	m_indices = {
		0, 2, 1,
		0, 3, 2
	};
}
