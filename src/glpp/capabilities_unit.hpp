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

#ifndef GLPP_CAPABILITIES_UNIT_HPP_INCLUDED
#define GLPP_CAPABILITIES_UNIT_HPP_INCLUDED

#include "base.hpp"
#include <vector>

namespace glpp {

	//! Unit to query OpenGL implementation capabilities
	/**
	 * @remarks non-copyable, non-inheritable
	 * @ingroup context_unit
	 */
	struct capabilities_unit :
		public noncopyable{

		//! All units are friend of context
		friend class context;

		//! Return the major version of this implementation
		int version_major() const;

		//! Return the minor version of this implementation
		int version_minor() const;

		//! Get the vendor's implementation string
		std::string vendor_string() const;

		//! Get the name of the renderer
		std::string renderer_string() const;

		//! Get shading language string
		std::string shading_language_string() const;

		//! Total texture units
		size_t total_texture_units() const;

		//! Maximum texture size (rough estimation)
		int max_texture_size() const;

		//! Maximum size of 3d textures (rough estimation)
		int max_3d_texture_size() const;

		//! Maximum size of cube textures (rough estimation)
		int max_cube_texture_size() const;

		//! The value gives a rough estimate of the largest rectangular texture that the GL can handle
		int max_rectangle_texture_size() const;

		//! Maximum number of samples in a multisample depth or depth-stencil texture
		int max_depth_texture_samples() const;

		//! Maximum number of layers allowed in an array texture, and must be at least 256
		int max_array_texture_layers() const;

		//! The maximum number of simultaneous outputs that may be written in a fragment shader.
		int max_draw_buffers() const;

		//! The maximum number of active draw buffers when using dual-source  blending
		int max_dualsource_draw_buffers() const;

		//! The recommended maximum number of vertex array indices
		int max_elements_indices() const;

		//! The recommended maximum number of vertex array vertices
		int max_elements_vertices() const;

		//! Maximum number of atomic counters available to fragment shaders
		int max_fragment_atomic_counters() const;

		//! Maximum number of components of the inputs read by the fragment shader,
		int max_fragment_input_components() const;

		/**
		 * @brief Maximum number of individual floating-point, integer, or boolean values
		 * that can be held in uniform variable storage for a fragment shader
		 */
		int max_fragment_uniform_components() const;

		/**
		 * @brief the maximum number of individual 4-vectors of floating-point, integer,
		 * or boolean values that can be held in uniform variable storage for a fragment shader
		 */
		int max_fragment_uniform_vectors() const;

		//! The maximum number of uniform blocks per fragment shader
		int max_fragment_uniform_blocks() const;

		//! Maximum number of atomic counters available to geometry shaders.
		int max_geometry_atomic_counters() const;

		//! The maximum number of components of inputs read by a geometry shader
		/**
		 * It must be at least 64.
		 * */
		int max_geometry_input_components() const;

		//! Maximum number of components of outputs written by a geometry shader
		int max_geometry_output_components() const;

		//! Maximum supported texture image units that can be used to access texture maps from the geometry shader
		int max_geometry_texture_image_units() const;

		//! Maximum number of uniform blocks per geometry shader.
		int max_geometry_uniform_blocks() const;

		//! Maximum number of components in uniform variable storage for a geometry shader
		/**
		 * @brief Maximum number of individual floating-point, integer, or boolean values that can be held
		 * in uniform variable storage for a geometry shader
		 */
		int max_geometry_uniform_components() const;

		//! The maximum number of samples supported in integer format multisample buffers.
		int max_integer_samples() const;

		//! The minimum alignment in basic machine units of pointers
		int min_map_buffer_alignment() const;

		//! The maximum texel offset allowed in a texture lookup, which must be at least 7.
		int max_program_texel_offset() const;

		//! The minimum texel offset allowed in a texture lookup, which must be at most -8.
		int min_program_texel_offset() const;

		//! The value indicates the maximum supported size for renderbuffers
		int max_renderbuffers() const;

		//! Maximum number of sample mask words.
		int max_sample_mask_words() const;

		//! The maximum glWaitSync timeout interval.
		GLint64 max_server_wait_timeout() const;

		//! The maximum number of atomic counters available to tessellation control shaders
		int max_tess_control_atomic_counters() const;

		//! The maximum number of atomic counters available to tessellation evaluation shaders.
		int max_tess_evaluation_atomic_counters() const;

		//! The maximum number of texels allowed in the texel array of a texture buffer object. Value must be at least 65536.
		int max_texture_buffer_size() const;

		//! The maximum, absolute value of the texture level-of-detail bias. The value must be at least 2.0.
		float max_texture_lod_bias() const;

		//! The maximum number of uniform buffer binding points on the context, which must be at least 36
		int max_uniform_buffer_bindings() const;

		//! The maximum size in basic machine units of a uniform block, which must be at least 16384
		int max_uniform_block_size() const;

		//! The number components for varying variables, which must be at least 60.
		int max_varyings_components() const;

		//! the number 4-vectors for varying variables, which is equal to the value of GL_MAX_VARYING_COMPONENTS and must be at least 1
		int max_varying_vectors() const;

		//! The maximum number of interpolators available for processing varying variables used by vertex and fragment shaders
		int max_varying_floats() const;

		//! The maximum number of atomic counters available to vertex shaders.
		int max_vertex_atomic_counters() const;

		//! The maximum number of 4-component generic vertex attributes accessible to a vertex shader.
		int max_vertex_attribs() const;

		//! the maximum supported texture image units that can be used to access texture maps from the vertex shader.
		int max_vertex_texture_image_units() const;

		//! Maximum number of components in uniform variable storage for a vertex shader
		/**
		 * @brief Maximum number of individual floating-point, integer, or boolean values that can be held
		 * in uniform variable storage for a vertex shader
		 */
		int max_vertex_uniform_components() const;

		//! The maximum number of 4-vectors that may be held in uniform variable storage for the vertex shader.
		int max_vertex_uniform_vectors() const;

		//! The maximum number of components of output written by a vertex shader, which must be at least 64.
		int max_vertex_output_components() const;

		//! The maximum number of uniform blocks per vertex shader.
		int max_vertex_uniform_blocks() const;

		//! The maximum supported width and height of the viewport.
		void max_viewport_dims(int & width, int & height) const;

		//! The maximum number of simultaneous viewports that are supported.
		int max_viewports() const;

		//! Maximum number of application-defined clipping distances
		int max_clip_distances() const;

		//! Maximum number of samples in a color multisample texture
		int max_color_texture_samples() const;

		//! Maximum number of atomic counters available to all active shaders.
		int max_atomic_counters() const;

		//! The number of words for fragment shader uniform variables in all uniform blocks (including default)
		int max_combined_fragment_uniform_components() const;

		//! The number of words for geometry shader uniform variables in all uniform blocks (including default)
		int max_combined_geometry_uniform_components() const;

		//! The number of words for vertex shader uniform variables in all uniform blocks (including default)
		int max_combined_vertex_uniform_components() const;

		//! Maximum number of components in uniform variable storage for a fragment shader
		/**
		 * @brief Maximum number of individual floating-point, integer, or boolean values that can be held
		 * in uniform variable storage for a fragment shader
		 */
		int max_combined_texture_image_units() const;

		//! Maximum number of uniform blocks per program
		int max_combined_uniform_blocks() const;

		//! Get list with all supported compressed texture formats
		const std::vector<image_compressed_format> supported_compressed_formats() const;

		//! Check if a compressed format is supported
		bool is_compressed_format_supported(image_compressed_format format) const;

		//! Get the list with all supported extensions
		const std::vector<std::string> supported_extensions() const;

		//! Check if an extension is supported
		bool is_extension_supported(const std::string & name) const;

		//! Get the list with program binary formats that are support
		const std::vector<int> supported_program_binary_formats() const;

		//! Check if program binary format is supported
		bool is_program_binary_format_supported(int id) const;

		//! Check if implementation support shader binary format
		bool is_shader_binary_format_supported() const;

	protected:

		//! Construction is permitted only by glpp::context
		capabilities_unit(context & ctx);

		//! Reference to context that this is unit is part of.
		context & m_ctx;
	};
}

#endif
