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
#include "light.hpp"
#include <glm/gtc/type_ptr.hpp>

light::light():
	type(direction_enum::spot),
	position(0, 0, 0),
	orientation(0, 0, 0, 1),
	diffuse(1.0, 1.0, 1.0, 1.0),
	specular(1, 1, 1, 1),
	const_att_factor(1),
	lin_att_factor(0),
	quad_att_factor(0.02)
{

}

void light::set_uniforms(glpp::program * pprog, const std::string & prefix) {

	pprog->get_global_uniform(prefix + "position")->set3f(glm::value_ptr(position));
	pprog->get_global_uniform(prefix + "diffuse")->set4f(glm::value_ptr(diffuse));
	pprog->get_global_uniform(prefix + "specular")->set4f(glm::value_ptr(specular));
	pprog->get_global_uniform(prefix + "const_att_factor")->set1f(const_att_factor);
	pprog->get_global_uniform(prefix + "lin_att_factor")->set1f(lin_att_factor);
	pprog->get_global_uniform(prefix + "quad_att_factor")->set1f(quad_att_factor);
}
