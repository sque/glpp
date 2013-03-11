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

#ifndef GLPP_TESTS_GEOMETRY_HPP_INCLUDED
#define GLPP_TESTS_GEOMETRY_HPP_INCLUDED

#include "internal.hpp"
#include "material.hpp"
#include "effect.hpp"

//! A type to hold geometry
class geometry {
public:

	//! Vertices type
	typedef std::vector<glm::vec3> vertices_type;

	//! Normals type
	typedef std::vector<glm::vec3> normals_type;

	//! Texture coordinates type
	typedef std::vector<glm::vec3> texcoords_type;

	//! Indices type
	typedef std::vector<GLuint> indices_type;

	//! Tangents type
	typedef std::vector<glm::vec3> tangents_type;

	//! Bitangents type
	typedef std::vector<glm::vec3> bitangents_type;

	//! Position of geometry
	glm::vec3 position;

	//! Orientation of geometry
	glm::quat orientation;

	//! Geometry material
	::material material;

	// Default construct is empty
	geometry();

	// Construct from a model file
	geometry(const std::string & fname);

	// Destructor
	virtual ~geometry();

	//! Get vertex array of this geometry
	inline glpp::vertex_array & vao() {
		return * mp_vao;
	}

	//! Draw this geometry
	virtual void draw();

	//! Return true if it carries normals
	inline bool has_normals() {
		return m_normals.size();
	}

	//! Return true if it carries texture coordinates
	inline bool has_texcoords() {
		return m_texcoords.size();
	}

	//! Return true if it carries tanget and bitanget information
	inline bool has_tanget_and_bitangent() {
		return m_tangents.size();
	}

	//! Create objects
	virtual void create_globjects();

	//! Load a texture on model
	void load_texture(const std::string & fname);

	//! Attach texture
	void attach_texture(glpp::texture * ptex);

	inline void set_program(glpp::program * pprog) {
		mp_prog = pprog;
	}

	inline glpp::program & get_program() {
		return * mp_prog;
	}

	inline bool has_program() {
		return mp_prog != NULL;
	}

	inline effect & get_effect() {
		return *mp_fx;
	}

	inline bool has_effect() {
		return mp_fx != NULL;
	}

	effect * set_effect(effect * effect) {
		return mp_fx = effect;
	}

	glm::mat4 model_matrix();

protected:
	//! Array with all vertices
	vertices_type m_vertices;

	//! Array with all normals
	normals_type m_normals;

	//! Array with all tex coords
	texcoords_type m_texcoords;

	//! Array of tangents
	tangents_type m_tangents;

	//! Array of bitangnets
	bitangents_type m_bitangents;

	//! Array of normal indices
	indices_type m_indices;

	//! Pointer to buffer object that holds vertices and normals
	glpp::buffer * mp_vbo;

	//! Pointer to buffer object that holds vertices indices
	glpp::buffer * mp_ebo;

	//! Vertex array object
	glpp::vertex_array * mp_vao;

	//! Texture of this object
	glpp::texture * mp_tex;

	//! Optional program to use before rendering
	glpp::program * mp_prog;

	//! Optional effect to use for rendering
	effect  * mp_fx;
};

void load_texture_from_file(glpp::texture * ptex, glpp::tex2d_update_target target, const std::string & fname, bool vflip = false);

void load_texturecube_from_file(glpp::texture * ptex, const std::string & fname, bool vflip = false);
#endif
