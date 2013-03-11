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
#include "info.hpp"
#include "../context.hpp"
#include <sstream>
#include <iomanip>

namespace glpp {
namespace utils {

	std::string compressed_format_to_name(image_compressed_format format) {
		switch(format) {
		case image_compressed_format::COMPRESSED_RED: return "COMPRESSED_RED";
		case image_compressed_format::COMPRESSED_RED_RGTC1: return "COMPRESSED_RED_RGTC1";
		case image_compressed_format::COMPRESSED_RG: return "COMPRESSED_RG";
		case image_compressed_format::COMPRESSED_RGB: return "COMPRESSED_RGB";
		case image_compressed_format::COMPRESSED_RGBA: return "COMPRESSED_RGBA";
		case image_compressed_format::COMPRESSED_RG_RGTC2: return "COMPRESSED_RG_RGTC2";
		case image_compressed_format::COMPRESSED_SIGNED_RED_RGTC1: return "COMPRESSED_SIGNED_RED_RGTC1";
		case image_compressed_format::COMPRESSED_SIGNED_RG_RGTC2: return "COMPRESSED_SIGNED_RG_RGTC2";
		case image_compressed_format::COMPRESSED_SRGB: return "COMPRESSED_SRGB";
		case image_compressed_format::COMPRESSED_SRGB_ALPHA: return "COMPRESSED_SRGB_ALPHA";
		/*TODO GLEW 1.7
		case image_compressed_format::COMPRESSED_RGBA_BPTC_UNORM: return "COMPRESSED_RGBA_BPTC_UNORM";
		case image_compressed_format::COMPRESSED_RGB_BPTC_SIGNED_FLOAT: return "COMPRESSED_RGB_BPTC_SIGNED_FLOAT";
		case image_compressed_format::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT: return "COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT";
		case image_compressed_format::COMPRESSED_SRGB_ALPHA_BPTC_UNORM: return "COMPRESSED_SRGB_ALPHA_BPTC_UNORM";*/
		default: return "UNKNOWN";
		}
	}

	struct limit_entry{
		context_param_type param;
		std::string name;
	};

	#define LIMIT_ENTRY(x) { glpp::context_param_type::x, #x }

	std::vector<limit_entry> limit_names() {
		return std::vector<limit_entry>  {
			LIMIT_ENTRY(MAX_3D_TEXTURE_SIZE),
			LIMIT_ENTRY(MAX_ARRAY_TEXTURE_LAYERS),
			LIMIT_ENTRY(MAX_CLIP_DISTANCES),
			LIMIT_ENTRY(MAX_COLOR_TEXTURE_SAMPLES),

			LIMIT_ENTRY(MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_COMBINED_TEXTURE_IMAGE_UNITS),
			LIMIT_ENTRY(MAX_COMBINED_UNIFORM_BLOCKS),
			LIMIT_ENTRY(MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_CUBE_MAP_TEXTURE_SIZE),
			LIMIT_ENTRY(MAX_DEPTH_TEXTURE_SAMPLES),
			LIMIT_ENTRY(MAX_DRAW_BUFFERS),

			LIMIT_ENTRY(MAX_ELEMENTS_INDICES),
			LIMIT_ENTRY(MAX_ELEMENTS_VERTICES),

			LIMIT_ENTRY(MAX_FRAGMENT_INPUT_COMPONENTS),
			LIMIT_ENTRY(MAX_FRAGMENT_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_FRAGMENT_UNIFORM_VECTORS),
			LIMIT_ENTRY(MAX_FRAGMENT_UNIFORM_BLOCKS),

			LIMIT_ENTRY(MAX_GEOMETRY_INPUT_COMPONENTS),
			LIMIT_ENTRY(MAX_GEOMETRY_OUTPUT_COMPONENTS),
			LIMIT_ENTRY(MAX_GEOMETRY_TEXTURE_IMAGE_UNITS),
			LIMIT_ENTRY(MAX_GEOMETRY_UNIFORM_BLOCKS),
			LIMIT_ENTRY(MAX_GEOMETRY_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_INTEGER_SAMPLES),

			LIMIT_ENTRY(MAX_PROGRAM_TEXEL_OFFSET),
			LIMIT_ENTRY(MIN_PROGRAM_TEXEL_OFFSET),
			LIMIT_ENTRY(MAX_RECTANGLE_TEXTURE_SIZE),
			LIMIT_ENTRY(MAX_RENDERBUFFER_SIZE),
			LIMIT_ENTRY(MAX_SAMPLE_MASK_WORDS),
			LIMIT_ENTRY(MAX_SERVER_WAIT_TIMEOUT),

			LIMIT_ENTRY(MAX_TEXTURE_BUFFER_SIZE),
			LIMIT_ENTRY(MAX_TEXTURE_IMAGE_UNITS),
			LIMIT_ENTRY(MAX_TEXTURE_LOD_BIAS),
			LIMIT_ENTRY(MAX_TEXTURE_SIZE),
			LIMIT_ENTRY(MAX_UNIFORM_BUFFER_BINDINGS),
			LIMIT_ENTRY(MAX_UNIFORM_BLOCK_SIZE),
			LIMIT_ENTRY(MAX_VARYING_COMPONENTS),
			LIMIT_ENTRY(MAX_VARYING_VECTORS),
			LIMIT_ENTRY(MAX_VARYING_FLOATS),

			LIMIT_ENTRY(MAX_VERTEX_ATTRIBS),
			LIMIT_ENTRY(MAX_VERTEX_TEXTURE_IMAGE_UNITS),
			LIMIT_ENTRY(MAX_VERTEX_UNIFORM_COMPONENTS),
			LIMIT_ENTRY(MAX_VERTEX_UNIFORM_VECTORS),
			LIMIT_ENTRY(MAX_VERTEX_OUTPUT_COMPONENTS),
			LIMIT_ENTRY(MAX_VERTEX_UNIFORM_BLOCKS),

			LIMIT_ENTRY(MAX_VIEWPORTS),
		};
	}

	std::string info(context & ctx, bitflags<info_filter> filter) {
		std::ostringstream ss;

		ss << "OpenGL Version: " << ctx.capabilities().version_major() << "." << ctx.capabilities().version_minor() << std::endl;
		ss << "Shading Language: " << ctx.capabilities().shading_language_string() << std::endl;
		ss << "Vendor: " << ctx.capabilities().vendor_string() << std::endl;
		ss << "Renderer: " << ctx.capabilities().renderer_string() << std::endl;


		if (filter.has_flag(info_filter::LIMITS)) {
			ss << std::endl << "Implementation Limits:" << std::endl;
			ss << "--------------------------------------------" << std::endl;
			auto limits = limit_names();
			auto larget_name = std::max_element(limits.begin(), limits.end(), [](const limit_entry &a, const limit_entry & b ){
				return a.name.size() < b.name.size();
			});

			for(auto lim : limits) {
				ss << " " << std::setw(larget_name->name.size()) << std::left << lim.name << "  :" << ctx.get_param_int(lim.param) << std::endl;
			}
		}

		if (filter.has_flag(info_filter::EXTENSIONS)) {
			ss << std::endl << "Extensions:" << std::endl;
			ss << "--------------------------------------------" << std::endl;
			for(auto ext: ctx.capabilities().supported_extensions()) {
				ss << " " << ext << std::endl;
			}
		}

		if (filter.has_flag(info_filter::COMPRESSED_FORMATS)) {
			ss << std::endl << "Supported Compressed Formats:" << std::endl;
			ss << "--------------------------------------------" << std::endl;
			for(auto format : ctx.capabilities().supported_compressed_formats()) {
				ss << " " << compressed_format_to_name(format) << "(0x" << std::hex << (int)format << ")" << std::endl;
			}
		}

		if (filter.has_flag(info_filter::BINARY_FORMATS)) {
			ss << std::endl << "Compiled object formats:" << std::endl;
			ss << "--------------------------------------------" << std::endl;
			for(auto format : ctx.capabilities().supported_program_binary_formats()) {
				ss << " Program binary format: 0x" << std::hex << (int)format << std::endl;
			}
			ss << " * Shader binary support: " << std::boolalpha << ctx.capabilities().is_shader_binary_format_supported() << std::endl;
		}
		return ss.str();
	}

}
}
