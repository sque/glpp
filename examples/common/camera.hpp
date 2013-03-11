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

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glpp/glpp.hpp>


class camera {
public:

	camera(float fov, float aspect, float znear, float zfar);

	// Rotate camera around world center
	void rotate_world_center(float angle, const glm::vec3 & axis);

	void yaw_world_center(float angle);

	void pitch_world_center(float angle);

	void zoom_in(float z);

	void zoom_out(float z);

	inline const glm::mat4 & proj_matrix() const{
		return m_proj_matrix;
	}

	inline const glm::mat4 & view_matrix() const {
		return m_view_matrix;
	}

	inline float fov() const {
		return m_fov;
	}

	inline float aspect() const {
		return m_aspect;
	}

	inline float znear() const {
		return m_znear;
	}

	inline float zfar() const {
		return m_zfar;
	}

	inline glm::vec3 & position() {
		return m_position;
	}

	inline glm::quat & orientation() {
		return m_orientation;
	}

	inline float fov(float _fov) {
		return m_fov = _fov;
	}

	inline float aspect(float _aspect) {
		return m_aspect = _aspect;
	}

	inline float znear(float znear) {
		return m_znear = znear;
	}

	inline float zfar(float zfar) {
		return m_zfar = zfar;
	}

	inline glm::vec3 & position(const glm::vec3 & position ) {
		return m_position = position;
	}

	inline glm::quat & orientation(const glm::quat & orientation) {
		return m_orientation = orientation;
	}

	void recalculate_matrices();

protected:

	glm::mat4 m_proj_matrix;

	glm::mat4 m_view_matrix;

	float m_fov, m_aspect, m_znear, m_zfar;

	glm::vec3 m_position;

	glm::quat m_orientation;
};

#endif /* CAMERA_H_ */
