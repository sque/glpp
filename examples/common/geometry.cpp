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
#include "geometry.hpp"
#include <Importer.hpp>      // C++ importer interface
#include <scene.h>      // C++ importer interface
#include <postprocess.h>
#include <iostream>
#include <FreeImagePlus.h>
#include <glm/gtc/matrix_transform.hpp>

geometry::geometry()
	:mp_vbo(nullptr),
	 mp_ebo(nullptr),
	 mp_vao(nullptr),
	 mp_tex(nullptr),
	 mp_prog(nullptr),
	 mp_fx(nullptr){

	orientation = glm::quat(1,0,0,0);
	position = glm::vec3(0,0,0);
}

geometry::~geometry(){
	delete mp_vao;
	delete mp_vbo;
	delete mp_ebo;
}

// Construct from a model file
geometry::geometry(const std::string & fname) :
		mp_vbo(nullptr),
		mp_ebo(nullptr),
		mp_vao(nullptr),
		mp_tex(nullptr),
		mp_prog(nullptr),
		mp_fx(nullptr){	// TODO: delegated constructors

	orientation = glm::quat(1,0,0,0);
	position = glm::vec3(0,0,0);

	// Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll
		// propably to request more postprocessing than we do in this example.
		const aiScene* scene = importer.ReadFile(fname,
			aiProcess_CalcTangentSpace       |
			aiProcess_Triangulate            |
			aiProcess_JoinIdenticalVertices  |
			aiProcess_SortByPType);

		// If the import failed, report it
		if( !scene)	{
			std::cerr << importer.GetErrorString();
			throw std::invalid_argument("cannot open this file!");
		}

		if (scene->mNumMeshes == 0) {
			std::cerr << "This file has no meshes inside" << std::endl;
		}

		// Load vertices & normals
		aiMesh * pmesh = scene->mMeshes[0];
		m_vertices.resize(pmesh->mNumVertices);
		for(size_t i = 0; i < pmesh->mNumVertices; i++ ) {
			m_vertices[i] = *((glm::vec3 *)&pmesh->mVertices[i][0]);
		}
		if (pmesh->HasNormals()) {
			m_normals.resize(pmesh->mNumVertices);
			for(size_t i = 0; i < pmesh->mNumVertices; i++ ) {
				m_normals[i] = *((glm::vec3 *)&pmesh->mNormals[i][0]);
			}
		}
		if (pmesh->HasTextureCoords(0)) {
			m_texcoords.resize(pmesh->mNumVertices);
			for(size_t i = 0; i < pmesh->mNumVertices; i++ ) {
				m_texcoords[i] = *((glm::vec3 *)&pmesh->mTextureCoords[0][i][0]);
			}
		}

		if (pmesh->HasTangentsAndBitangents()) {
			m_tangents.resize(pmesh->mNumVertices);
			m_bitangents.resize(pmesh->mNumVertices);
			for(size_t i = 0; i < pmesh->mNumVertices; i++) {
				m_tangents[i] = *((glm::vec3 *)&pmesh->mTangents[i][0]);
				m_bitangents[i] = *((glm::vec3 *)&pmesh->mBitangents[i][0]);
			}
		}
		// Load faces indices (triangles)
		m_indices.resize(pmesh->mNumFaces * 3);
		for(size_t i =0;i < pmesh->mNumFaces;i++) {
			m_indices[i * 3] = pmesh->mFaces[i].mIndices[0];
			m_indices[i * 3 + 1] = pmesh->mFaces[i].mIndices[1];
			m_indices[i * 3 + 2] = pmesh->mFaces[i].mIndices[2];
		}
}

void geometry::create_globjects() {
	size_t sz_vertices = sizeof(vertices_type::value_type) * m_vertices.size();
	size_t sz_normals = sizeof(normals_type::value_type) * m_normals.size();
	size_t sz_texcoords = sizeof(texcoords_type::value_type) * m_normals.size();
	size_t sz_tangents = sizeof(tangents_type::value_type) * m_tangents.size();
	size_t sz_bitangents = sizeof(tangents_type::value_type) * m_tangents.size();
	size_t sz_total = sz_vertices + sz_normals + sz_texcoords + sz_tangents + sz_bitangents;

	// Create VBI with vertices and normals
	mp_vbo = new glpp::buffer(glpp::buffer_type::ARRAY);
	glpp::assert_no_glerror("Cannot create buffer.");

	mp_vbo->define_data(sz_total, NULL, glpp::buffer_usage_pattern::STATIC_DRAW);
	glpp::assert_no_glerror("Cannot define buffer data.");

	// Set data
	mp_vbo->update_subdata(0, sz_vertices, &m_vertices[0]);
	mp_vbo->update_subdata(sz_vertices, sz_normals, &m_normals[0]);
	mp_vbo->update_subdata(sz_vertices + sz_normals, sz_texcoords, &m_texcoords[0]);
	mp_vbo->update_subdata(sz_vertices + sz_normals + sz_texcoords, sz_tangents, &m_tangents[0]);
	mp_vbo->update_subdata(sz_vertices + sz_normals + sz_texcoords + sz_tangents, sz_bitangents, &m_bitangents[0]);
	glpp::assert_no_glerror("Cannot update buffer data.");

	// Create Elements
	mp_ebo = new glpp::buffer(glpp::buffer_type::ELEMENT_ARRAY);
	glpp::assert_no_glerror("Cannot create indices buffer.");
	mp_ebo->define_data(sizeof(indices_type::value_type) * m_indices.size(), &m_indices[0], glpp::buffer_usage_pattern::STATIC_DRAW);
	glpp::assert_no_glerror("Cannot define indices buffer.");

	// Create VAO
	mp_vao = new glpp::vertex_array();
	glpp::assert_no_glerror("Cannot create vertex array.");
	mp_vao->attrib(0)->set_pointerf(*mp_vbo, 3, glpp::attribf_data_type::FLOAT);
	mp_vao->attrib(0)->enable();
	mp_vao->attrib(1)->set_pointerf(*mp_vbo, 3, glpp::attribf_data_type::FLOAT, 0, sz_vertices);
	mp_vao->attrib(1)->enable();
	mp_vao->attrib(2)->set_pointerf(*mp_vbo, 3, glpp::attribf_data_type::FLOAT, 0, sz_vertices + sz_normals);
	mp_vao->attrib(2)->enable();

	if (has_tanget_and_bitangent()) {
		mp_vao->attrib(3)->set_pointerf(*mp_vbo, 3, glpp::attribf_data_type::FLOAT, 0, sz_vertices + sz_normals + sz_texcoords);
		mp_vao->attrib(3)->enable();
		mp_vao->attrib(4)->set_pointerf(*mp_vbo, 3, glpp::attribf_data_type::FLOAT, 0, sz_vertices + sz_normals + sz_texcoords + sz_tangents);
		mp_vao->attrib(4)->enable();
	}

	glpp::assert_no_glerror("Cannot update vertex array attributes.");
}

glm::mat4 geometry::model_matrix() {
	glm::mat4 mm = glm::translate(glm::mat4(1.0f), position);
	mm *= glm::mat4_cast(orientation);
	return mm;
}

//! Load a texture on model
void geometry::load_texture(const std::string & fname) {
	mp_tex = new glpp::texture(glpp::texture_type::TEX_2D);
	load_texture_from_file(mp_tex, glpp::tex2d_update_target::TEX_2D, fname);
	glpp::current_ctx().texture_unit(0).bind_texture(*mp_tex);
}

void geometry::draw() {
	if (has_program())
		mp_prog->use();

	if (has_effect())
		mp_fx->get_program().use();

	mp_vao->draw_elements(m_indices.size(), *mp_ebo, glpp::elements_type::UNSIGNED_INT);
}

void geometry::attach_texture(glpp::texture * ptex) {
	mp_tex = ptex;
}

void _load_texture_from_fip(glpp::texture * ptex, glpp::tex2d_update_target target, fipImage & img, bool vflip) {

	std::cout << "Loading image (w,h) = " << img.getWidth() << "," << img.getHeight() << std::endl;
	img.convertTo32Bits();

	size_t total_pixels = img.getHeight() * img.getWidth();
	unsigned char * ppixels = new unsigned char[total_pixels * 32];


	FreeImage_ConvertToRawBits((unsigned char *) ppixels, img, img.getLine(),
			32, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, vflip);



	glpp::assert_no_glerror("Cannot create texture.");

	ptex->define_data_2d(
		target,		//Target
		0,			//level
		glpp::image_format::RGBA,	// Internal format
		img.getWidth(),	//Width
		img.getHeight(),
		0,			//border
		glpp::pixel_format::BGRA,
		glpp::tex_pixel_type::UNSIGNED_BYTE,
		ppixels);
	glpp::assert_no_glerror("Cannot update texture data.");

}

void load_texture_from_file(glpp::texture * ptex, glpp::tex2d_update_target target, const std::string & fname, bool vflip ) {
	fipImage img;

	if (!img.load(fname.c_str()) ) {
		std::cerr << "Cannot open image: " << fname << std::endl;
		throw std::invalid_argument("cannot open this file!");
	}

	_load_texture_from_fip(ptex, target, img, vflip);

	ptex->set_max_level(10);
	ptex->set_min_filter(glpp::min_filter_type::LINEAR_MIPMAP_LINEAR);
	ptex->set_mag_filter(glpp::mag_filter_type::LINEAR);
	ptex->generate_mipmaps();
	glpp::assert_no_glerror("Cannot change texture parameters.");
}

void load_texturecube_from_file(glpp::texture * ptex, const std::string & fname, bool vflip) {
	fipImage img;

	if (!img.load(fname.c_str()) ) {
		std::cerr << "Cannot open image: " << fname << std::endl;
		throw std::invalid_argument("cannot open this file!");
	}

	int side_width = img.getWidth()/4;
	int side_height = img.getHeight()/3;
	fipImage front = img; front.crop(side_width*3, side_height, side_width*4, side_height*2);
	fipImage right = img; right.crop(side_width*2, side_height, side_width*3, side_height*2);
	fipImage left = img; left.crop(0, side_height, side_width, side_height*2);
	fipImage back = img; back.crop(side_width, side_height, side_width*2, side_height*2);
	fipImage top = img; top.crop(side_width, 0, side_width*2, side_height);
	fipImage bottom = img; bottom.crop(side_width, side_height*2, side_width*2, side_height*3);

	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_NEGATIVE_Z, front, vflip);
	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_POSITIVE_X, right, vflip);
	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_NEGATIVE_X, left, vflip);
	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_POSITIVE_Z, back, vflip);
	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_POSITIVE_Y, top, vflip);
	_load_texture_from_fip(ptex, glpp::tex2d_update_target::TEX_CUBE_MAP_NEGATIVE_Y, bottom, vflip);

	ptex->set_min_filter(glpp::min_filter_type::LINEAR_MIPMAP_LINEAR);
	ptex->set_mag_filter(glpp::mag_filter_type::LINEAR);
	ptex->set_wrap_r(glpp::wrap_type::CLAMP_TO_EDGE);
	ptex->set_wrap_s(glpp::wrap_type::CLAMP_TO_EDGE);
	ptex->set_wrap_t(glpp::wrap_type::CLAMP_TO_EDGE);
	ptex->generate_mipmaps();
}

