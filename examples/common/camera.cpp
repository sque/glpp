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
#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

camera::camera(float fov, float aspect, float znear, float zfar):
	m_fov(fov),
	m_aspect(aspect),
	m_znear(znear),
	m_zfar(zfar),
	m_position(0, 0, 10),
	m_orientation(1, 0, 0, 0){

}

// Rotate camera around world center
void camera::rotate_world_center(float angle, const glm::vec3 & axis) {
	m_position = glm::rotate(m_position, angle, axis);
	m_orientation = glm::rotate(m_orientation, -angle, axis);
}

void camera::yaw_world_center(float angle) {
	rotate_world_center(angle, glm::vec3(0,1,0));
}

void camera::pitch_world_center(float angle) {
	glm::vec3 local_y = glm::cross(m_position, glm::vec3(0,1,0));
	rotate_world_center(angle, local_y);
}

void camera::recalculate_matrices(){
	m_proj_matrix = glm::perspective(m_fov, m_aspect, m_znear, m_zfar);
	m_view_matrix = glm::mat4_cast(glm::normalize(m_orientation));
	m_view_matrix = glm::translate(m_view_matrix, -m_position);
}


void camera::zoom_in(float z) {
	float l = glm::length(m_position);
	if (l - z < 0)
		return;
	m_position *= (l -z)/l;
}

void camera::zoom_out(float z) {

	float l = glm::length(m_position);
	m_position *= (l + z)/l;
}
