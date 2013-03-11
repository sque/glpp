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

#ifndef GLPP_TESTS_LIGHT_HPP_INCLUDED
#define GLPP_TESTS_LIGHT_HPP_INCLUDED

#include <glpp/glpp.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


class light {
public:

	enum class direction_enum {
		spot,
		directional
	};

	//! Light type
	direction_enum type;

	glm::vec3 position;
	glm::quat orientation;

	//! Light characteristics
	glm::vec4 diffuse;
	glm::vec4 specular;

	float const_att_factor;

	float lin_att_factor;

	float quad_att_factor;

	//! Construct a light
	light();

	void set_uniforms(glpp::program * pprog, const std::string & prefix);
};
#endif
