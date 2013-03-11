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
#include "capabilities_unit.hpp"
#include "context.hpp"

namespace glpp {

capabilities_unit::capabilities_unit(context & ctx) :
	m_ctx(ctx) {

}

int capabilities_unit::version_major() const {
	return m_ctx.get_param_int(context_param_type::MAJOR_VERSION);
}

//! Return the minor version of this implementation
int capabilities_unit::version_minor() const {
	return m_ctx.get_param_int(context_param_type::MINOR_VERSION);
}

//! Get the vendor's implementation string
std::string capabilities_unit::vendor_string() const {
	return (char *)glGetString(GL_VENDOR);
}

//! Get the name of the renderer
std::string capabilities_unit::renderer_string() const {
	return (char *)::glGetString(GL_RENDERER);
}

//! Get shading language string
std::string capabilities_unit::shading_language_string() const {
	return (char *)::glGetString(GL_SHADING_LANGUAGE_VERSION);
}

//! Total texture units
size_t capabilities_unit::total_texture_units() const {
	return m_ctx.get_param_int(context_param_type::MAX_TEXTURE_IMAGE_UNITS);
}

//! Maximum texture size
int capabilities_unit::max_texture_size() const {
	return m_ctx.get_param_int(context_param_type::MAX_TEXTURE_SIZE);
}

//! Get list with all supported compressed texture formats
const std::vector<image_compressed_format> capabilities_unit::supported_compressed_formats() const {
	int total = m_ctx.get_param_int(context_param_type::NUM_COMPRESSED_TEXTURE_FORMATS);
	std::vector<int> gl_formats = m_ctx.get_param_intv(context_param_type::COMPRESSED_TEXTURE_FORMATS, total);

	std::vector<image_compressed_format> formats;
	std::vector<int>::iterator glit;
	for(glit = gl_formats.begin();glit != gl_formats.end(); glit ++) {
		formats.push_back(GLPP_CAST_TO_SAFE_ENUM(image_compressed_format, *glit));
	}
	return formats;
}

//! Check if a compressed format is supported
bool capabilities_unit::is_compressed_format_supported(image_compressed_format format) const {
	std::vector<image_compressed_format> formats = supported_compressed_formats();


	std::vector<image_compressed_format>::iterator it
		= std::find(formats.begin(), formats.end(), format);
	return (it != formats.end());
}

//! Get the list with all supported extensions
const std::vector<std::string> capabilities_unit::supported_extensions() const {
	int total = m_ctx.get_param_int(context_param_type::NUM_EXTENSIONS);

	std::vector<std::string> extensions;
	for(int i = 0;i < total;i++)
		extensions.push_back((char *)glGetStringi(GL_EXTENSIONS, i));

	return extensions;
}

//! Check if an extension is supported
bool capabilities_unit::is_extension_supported(const std::string & name) const{
	std::vector<std::string> extensions = supported_extensions();

	std::vector<std::string>::iterator it;
	it = std::find(extensions.begin(), extensions.end(), name);
	return (it != extensions.end());
}

//! Get the list with program binary formats that are support
const std::vector<int> capabilities_unit::supported_program_binary_formats() const {
	int total = m_ctx.get_param_int(context_param_type::NUM_PROGRAM_BINARY_FORMATS);

	return m_ctx.get_param_intv(context_param_type::PROGRAM_BINARY_FORMATS, total);
}

//! Check if program binary format is supported
bool capabilities_unit::is_program_binary_format_supported(int id) const {
	std::vector<int> formats = supported_program_binary_formats();
	return (std::count(formats.begin(), formats.end(), id) > 0);
}

//! Check if implementation support shader binary format
bool capabilities_unit::is_shader_binary_format_supported() const {
	return m_ctx.get_param_int(context_param_type::NUM_SHADER_BINARY_FORMATS);
}



int capabilities_unit::max_3d_texture_size() const{
	return m_ctx.get_param_int(context_param_type::MAX_3D_TEXTURE_SIZE);
}

int capabilities_unit::max_cube_texture_size() const{
	return m_ctx.get_param_int(context_param_type::MAX_CUBE_MAP_TEXTURE_SIZE);
}

int capabilities_unit::max_rectangle_texture_size() const{
return m_ctx.get_param_int(context_param_type::MAX_RECTANGLE_TEXTURE_SIZE);
}

int capabilities_unit::max_depth_texture_samples() const{
	return m_ctx.get_param_int(context_param_type::MAX_DEPTH_TEXTURE_SAMPLES);
}

int capabilities_unit::max_array_texture_layers() const{
	return m_ctx.get_param_int(context_param_type::MAX_ARRAY_TEXTURE_LAYERS);
}

int capabilities_unit::max_draw_buffers() const{
	return m_ctx.get_param_int(context_param_type::MAX_DRAW_BUFFERS);
}

int capabilities_unit::max_dualsource_draw_buffers() const{
	//TODO Glew 1.7 return m_ctx.get_param_int(context_param_type::MAX_DEPTH_TEXTURE_SAMPLES);
}

int capabilities_unit::max_elements_indices() const{
	return m_ctx.get_param_int(context_param_type::MAX_ELEMENTS_INDICES);
}

int capabilities_unit::max_elements_vertices() const{
	return m_ctx.get_param_int(context_param_type::MAX_ELEMENTS_VERTICES);
}

int capabilities_unit::max_fragment_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_FRAGMENT_ATOMIC_COUNTERS);
}

int capabilities_unit::max_fragment_input_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_FRAGMENT_INPUT_COMPONENTS);
}

int capabilities_unit::max_fragment_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_FRAGMENT_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_fragment_uniform_vectors() const{
	return m_ctx.get_param_int(context_param_type::MAX_FRAGMENT_UNIFORM_VECTORS);
}

int capabilities_unit::max_fragment_uniform_blocks() const{
	return m_ctx.get_param_int(context_param_type::MAX_FRAGMENT_UNIFORM_BLOCKS);
}

int capabilities_unit::max_geometry_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_ATOMIC_COUNTERS);
}

int capabilities_unit::max_geometry_input_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_INPUT_COMPONENTS);
}

int capabilities_unit::max_geometry_output_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_OUTPUT_COMPONENTS);
}

int capabilities_unit::max_geometry_texture_image_units() const{
	return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_TEXTURE_IMAGE_UNITS);
}

int capabilities_unit::max_geometry_uniform_blocks() const{
	return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_UNIFORM_BLOCKS);
}

int capabilities_unit::max_geometry_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_GEOMETRY_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_integer_samples() const{
	return m_ctx.get_param_int(context_param_type::MAX_INTEGER_SAMPLES);
}

int capabilities_unit::min_map_buffer_alignment() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MIN_MAP_BUFFER_ALIGNMENT);
}

int capabilities_unit::max_program_texel_offset() const{
	return m_ctx.get_param_int(context_param_type::MAX_PROGRAM_TEXEL_OFFSET);
}

int capabilities_unit::min_program_texel_offset() const{
	return m_ctx.get_param_int(context_param_type::MIN_PROGRAM_TEXEL_OFFSET);
}

int capabilities_unit::max_renderbuffers() const{
	return m_ctx.get_param_int(context_param_type::MAX_RENDERBUFFER_SIZE);
}

int capabilities_unit::max_sample_mask_words() const{
	return m_ctx.get_param_int(context_param_type::MAX_SAMPLE_MASK_WORDS);
}

GLint64 capabilities_unit::max_server_wait_timeout() const {
	return m_ctx.get_param_int64(context_param_type::MAX_SERVER_WAIT_TIMEOUT);
}

int capabilities_unit::max_tess_control_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_TESS_CONTROL_ATOMIC_COUNTERS);
}

int capabilities_unit::max_tess_evaluation_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_TESS_EVALUATION_ATOMIC_COUNTERS);
}

int capabilities_unit::max_texture_buffer_size() const{
	return m_ctx.get_param_int(context_param_type::MAX_TEXTURE_BUFFER_SIZE);
}

float capabilities_unit::max_texture_lod_bias() const {
	return m_ctx.get_param_float(context_param_type::MAX_TEXTURE_LOD_BIAS);
}

int capabilities_unit::max_uniform_buffer_bindings() const{
	return m_ctx.get_param_int(context_param_type::MAX_UNIFORM_BUFFER_BINDINGS);
}

int capabilities_unit::max_uniform_block_size() const{
	return m_ctx.get_param_int(context_param_type::MAX_UNIFORM_BLOCK_SIZE);
}

int capabilities_unit::max_varyings_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_VARYING_COMPONENTS);
}

int capabilities_unit::max_varying_vectors() const{
	return m_ctx.get_param_int(context_param_type::MAX_VARYING_VECTORS);
}

int capabilities_unit::max_varying_floats() const{
	return m_ctx.get_param_int(context_param_type::MAX_VARYING_FLOATS);
}

int capabilities_unit::max_vertex_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_VERTEX_ATOMIC_COUNTERS);
}

int capabilities_unit::max_vertex_attribs() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_ATTRIBS);
}

int capabilities_unit::max_vertex_texture_image_units() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_TEXTURE_IMAGE_UNITS);
}

int capabilities_unit::max_vertex_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_vertex_uniform_vectors() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_UNIFORM_VECTORS);
}

int capabilities_unit::max_vertex_output_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_OUTPUT_COMPONENTS);
}

int capabilities_unit::max_vertex_uniform_blocks() const{
	return m_ctx.get_param_int(context_param_type::MAX_VERTEX_UNIFORM_BLOCKS);
}

void capabilities_unit::max_viewport_dims(int & width, int & height) const {
	std::vector<int> dims =  m_ctx.get_param_intv(context_param_type::MAX_VIEWPORT_DIMS, 2);
	width = dims[0];
	height = dims[1];
}

int capabilities_unit::max_viewports() const{
	return m_ctx.get_param_int(context_param_type::MAX_VIEWPORTS);
}

int capabilities_unit::max_clip_distances() const{
	return m_ctx.get_param_int(context_param_type::MAX_CLIP_DISTANCES);
}

int capabilities_unit::max_color_texture_samples() const{
	return m_ctx.get_param_int(context_param_type::MAX_COLOR_TEXTURE_SAMPLES);
}

int capabilities_unit::max_atomic_counters() const{
	// TODO GLEW 1.7 return m_ctx.get_param_int(context_param_type::MAX_ATO);
}

int capabilities_unit::max_combined_fragment_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_combined_geometry_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_combined_vertex_uniform_components() const{
	return m_ctx.get_param_int(context_param_type::MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
}

int capabilities_unit::max_combined_texture_image_units() const{
	return m_ctx.get_param_int(context_param_type::MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

int capabilities_unit::max_combined_uniform_blocks() const{
	return m_ctx.get_param_int(context_param_type::MAX_COMBINED_UNIFORM_BLOCKS);
}


}
