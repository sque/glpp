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
#include "context.hpp"

namespace glpp {


	context * _curr_ctx = NULL;

	context::context() :
		m_depth_test(*this),
		m_stencil_test(*this),
		m_scissor_test(*this),
		m_blend_unit(*this),
		m_logicop_unit(*this),
		m_capabilities(*this),
		m_face_cull(*this){

		for(texture_unit_t::name_type tu = 0; tu < m_capabilities.total_texture_units();tu++) {
			m_texture_units.push_back(new texture_unit_t(*this, GL_TEXTURE0+tu));
		}
	}

	context::~context(){
		texture_unit_collection::iterator it;
		for(it = m_texture_units.begin(); it != m_texture_units.end(); it++) {
			delete *it;
		}
	}

	bool context::create() {
		if (_curr_ctx == NULL)
			_curr_ctx = new context();
		return true;
	}

	bool context::get_param_bool(context_param_type pname) const {
		GLboolean v;
		::glGetBooleanv(GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}

	GLint context::get_param_int(context_param_type pname) const{
		GLint v;
		::glGetIntegerv(GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}

	GLint64 context::get_param_int64(context_param_type pname) const{
		GLint64 v;
		::glGetInteger64v(GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}

	GLfloat context::get_param_float(context_param_type pname) const{
		GLfloat v;
		::glGetFloatv(GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}

	GLdouble context::get_param_double(context_param_type pname) const{
		GLdouble v;
		::glGetDoublev(GLPP_CAST_TO_SCALAR(GLenum, pname), &v);
		return v;
	}

	std::vector<int> context::get_param_intv(context_param_type pname, size_t size) {
		std::vector<int> res(size);
		::glGetIntegerv(GLPP_CAST_TO_SCALAR(GLenum, pname), &res[0]);
#		if ( GLPP_LANG == GLPP_LANG_CXX11)
			return std::move(res);
#		else
			return res;
#		endif
	}


	std::vector<GLint64> context::get_param_int64v(context_param_type pname, size_t size) {
		std::vector<GLint64> res(size);
		::glGetInteger64v(GLPP_CAST_TO_SCALAR(GLenum, pname), &res[0]);
#		if ( GLPP_LANG == GLPP_LANG_CXX11)
			return std::move(res);
#		else
			return res;
#		endif
	}

	std::vector<float> context::get_param_floatv(context_param_type pname, size_t size) {
		std::vector<float> res(size);
		::glGetFloatv(GLPP_CAST_TO_SCALAR(GLenum, pname), &res[0]);
#		if ( GLPP_LANG == GLPP_LANG_CXX11)
			return std::move(res);
#		else
			return res;
#		endif
	}

	std::vector<double> context::get_param_doublev(context_param_type pname, size_t size) {
		std::vector<double> res(size);
		::glGetDoublev(GLPP_CAST_TO_SCALAR(GLenum, pname), &res[0]);
#		if ( GLPP_LANG == GLPP_LANG_CXX11)
			return std::move(res);
#		else
			return res;
#		endif
	}


	//! Get a specific texture_unit
	texture_unit_t & context::texture_unit(size_t index){
		return *m_texture_units.at(index);
	}

	//! Get the name of the active texture unit
	size_t context::active_texture_unit() const{
		return get_param_int(context_param_type::ACTIVE_TEXTURE) - GL_TEXTURE0;
	}

	context & current_ctx() throw(no_active_context){
		if (_curr_ctx == NULL)
			throw no_active_context();
		return * _curr_ctx;
	}



}
