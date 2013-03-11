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

#ifndef TEST_SCENE_HPP_INCLUDED
#define TEST_SCENE_HPP_INCLUDED

#include "internal.hpp"
#include "geometry.hpp"
#include "light.hpp"
#include "camera.hpp"
#include <vector>
#include <unordered_map>


/***
 *  UNIFORMS DEFINED BY THIS SCENE
 *
 *  CameraPositionWs
 *
 *  ModelViewMatrix
 *
 *  ViewMatrix
 *
 *  ModelMatrix
 *
 *  ProjectionMatrix
 *
 *  lights[x].specular
 *
 *  lights[x].ambient
 *
 *  lights[x].diffuse
 */
class scene {
public:

	typedef std::unordered_map<std::string, geometry*> objects_type;

	typedef std::vector<light*> lights_type;

	geometry *  attach_object(const std::string & name, geometry * pobj) {
		return m_objects[name] = pobj;
	}

	size_t attach_light(light & lit) {
		m_lights.push_back(&lit);
		return m_lights.size() -1;
	}

	void draw();

	camera & get_camera() {
		return m_camera;
	}

	objects_type & objects() {
		return m_objects;
	}

	lights_type & lights() {
		return m_lights;
	}

	light & get_light(size_t index) {
		return *m_lights[index];
	}

	geometry & get_object(const std::string & name) {
		return *m_objects[name];
	}

	scene();

	void create_globjects();

protected:

	void set_uniforms(glpp::program * pprog, const glm::mat4 & model_matrix, material & mat);

	camera m_camera;

	objects_type m_objects;

	lights_type m_lights;
};


#endif
