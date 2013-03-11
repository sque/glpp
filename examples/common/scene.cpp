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
#include "scene.hpp"
#include <boost/format.hpp>
#include <glm/gtc/type_ptr.hpp>


scene::scene() :
	m_camera(40.0f, 4/3, 0.1f, 1000.f){
}

void scene::draw() {

	m_camera.recalculate_matrices();

	// Draw all geometries
	for(auto obj: m_objects) {
		geometry * pobj = std::get<1>(obj);
		if (pobj->has_program()) {
			set_uniforms(&pobj->get_program(), pobj->model_matrix(), pobj->material);
		}
		if (pobj->has_effect()) {
			set_uniforms(&pobj->get_effect().get_program(), pobj->model_matrix(), pobj->material);
		}
		pobj->draw();
	}

}

void scene::set_uniforms(glpp::program * pprog, const glm::mat4 & model_matrix, material & mat) {
	glm::mat4 mv =  m_camera.view_matrix() * model_matrix;

	pprog->get_global_uniform("CameraPositionWs")->set3f(glm::value_ptr(m_camera.position()));
	if (pprog->uniform_exists("ViewMatrix"))
		pprog->get_global_uniform("ViewMatrix")->setmat4f(glm::value_ptr(m_camera.view_matrix()), false);
	pprog->get_global_uniform("ProjectionMatrix")->setmat4f(glm::value_ptr(m_camera.proj_matrix()), false);
	pprog->get_global_uniform("ModelViewMatrix")->setmat4f(glm::value_ptr(mv), false);
	pprog->get_global_uniform("ModelMatrix")->setmat4f(glm::value_ptr(model_matrix), false);

	pprog->get_global_uniform("ambient")->set4f(0.2, 0.2, 0.2, 1);
	pprog->get_global_uniform("mat.emission")->set4f(glm::value_ptr(mat.emission));
	pprog->get_global_uniform("mat.specular")->set4f(glm::value_ptr(mat.specular));
	pprog->get_global_uniform("mat.shininess")->set1f(mat.shininess);
	pprog->get_global_uniform("mat.ambient")->set4f(glm::value_ptr(mat.ambient));
	pprog->get_global_uniform("mat.diffuse")->set4f(glm::value_ptr(mat.diffuse));
	if (pprog->uniform_exists("pulse"))
		pprog->get_global_uniform("pulse")->set1f(clock() % 1123123);

	// Draw all lights
	if (pprog->uniform_exists("lights"))
		pprog->get_global_uniform("lights")->set1i(m_lights.size());
	m_lights[0]->set_uniforms(pprog, "light[0].");
	m_lights[1]->set_uniforms(pprog, "light[1].");
	/*int i = 0;
	for(light * plit : m_lights) {
		std::string prefix = boost::format("light[%1%].") % i;
		plit.set_uniforms(pprog, prefix);
		i++;
	}*/
}

void scene::create_globjects() {

	for(auto obj: m_objects) {
		std::get<1>(obj)->create_globjects();
	}
}
