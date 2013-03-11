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

#ifndef GLPP_TEXTURE_HPP_INCLUDED
#define GLPP_TEXTURE_HPP_INCLUDED
#include "base.hpp"

namespace glpp {

	//! Object that represents an in-GPU texture.
	/**
	 * @remarks non-copyable, non-inheritable, RAII
	 * @todo missing define_data_..() functions
	 * @todo missing query information about texture levels.
	 * @ingroup gpu_buffer
	 */
	struct texture :
		public named_object<GLuint>,
		public noncopyable {

		//! Construct an empty texture object
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGenTextures.xml
		 * @param type Is the type of this texture.
		 */
		texture(const texture_type & type);

		//! Destroy and release resources of buffer
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glDeleteTextures.xml
		 */
		~texture();

		//! Get the type of texture as defined in constructor
		inline texture_type type() const {
			return m_tex_type;
		}

		//! Bind texture to its defined type target.
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glBindTexture.xml
		 */
		inline void bind() const {
			::glBindTexture(GLPP_CAST_TO_SCALAR(GLenum, type()), object_name());
		}

		//! @name Set texture parameters
		//! @{
		//! http://www.opengl.org/sdk/docs/man4/xhtml/glTexParameter.xml

		//! Define the border values that should be used for border texels
		void set_border_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

		//! Specifies the texture comparison mode for currently bound depth textures
		void set_compare_mode(compare_mode cm);

		//! Specifies the comparison operator used when @ref set_compare_mode() is set to REF_TO_TEXTURE
		void set_compare_func(compare_func cf);

		//! Specifies a fixed bias value that is to be added to the level-of-detail parameter for the texture before texture sampling.
		void set_lod_bias(GLfloat bias);

		//! Specify the minifying function
		void set_min_filter(min_filter_type mf);

		//! Specify the magnification function
		void set_mag_filter(mag_filter_type mf);

		//! Sets the minimum level-of-detail parameter
		/**
		 * The initial value is -1000.
		 */
		void set_min_lod(GLfloat lod);

		//! Sets the maximum level-of-detail parameter
		/**
		 * The initial value is 1000.
		 */
		void set_max_lod(GLfloat lod);

		//! Specifies the index of the lowest defined mipmap level.
		/**
		 *  This is an integer value. The initial value is 0.
		 */
		void set_base_level(GLint lvl);

		//! Sets the index of the highest defined mipmap level.
		/**
		 * This is an integer value. The initial value is 1000.
		 */
		void set_max_level(GLint lvl);

		//! Sets the swizzle that will be applied to the components of a texel before it is returned to the shader.
		void set_swizzle(swizzle_type r, swizzle_type g, swizzle_type b, swizzle_type a);

		//! Sets the wrap parameter for texture coordinate s
		void set_wrap_s(wrap_type ws);

		//! Sets the wrap parameter for texture coordinate t
		void set_wrap_t(wrap_type wt);

		//! Sets the wrap parameter for texture coordinate r
		void set_wrap_r(wrap_type wr);

		//! @}


		//! @name Set texture parameters
		//! @{
		//! http://www.opengl.org/sdk/docs/man4/xhtml/glGetTexParameter.xml

		//! Returns the single-valued base texture mipmap level.
		GLint get_base_level() const;

		//! Returns the single-valued maximum texture mipmap array level.
		GLint get_max_level() const;

		//! Returns four integer or floating-point numbers that comprise the RGBA color of the texture border.
		void get_border_color(GLfloat * rgba) const;

		//! Returns four integer or floating-point numbers that comprise the RGBA color of the texture border.
		void get_border_color(GLfloat & r, GLfloat & g, GLfloat & b, GLfloat & a) const;

		//! Returns the comparison mode
		compare_mode get_compare_mode() const;

		//! Returns the comparison functions when comparison mode is set to REF_TO_TEXTURE
		compare_func get_compare_func() const;

		//! Gets the minimum level-of-detail parameter
		GLfloat get_min_lod() const;

		//! Gets the maximum level-of-detail parameter
		GLfloat get_max_lod() const ;

		//! Gets the swizzle that will be applied to the components of a texel before it is returned to the shader.
		void get_swizzle(swizzle_type & r, swizzle_type & g, swizzle_type & b, swizzle_type & a) const;

		//! Sets the wrap parameter for texture coordinate s
		wrap_type get_wrap_s() const;

		//! Sets the wrap parameter for texture coordinate t
		wrap_type get_wrap_t() const;

		//! Sets the wrap parameter for texture coordinate r
		wrap_type get_wrap_r() const;

		//! Returns true if the texture has an immutable format.
		bool is_immutable_format() const;

		//! @}

		//! Specify a two-dimensional texture image
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glTexImage2D.xml
		 */
		void define_data_2d(tex2d_update_target target,
				GLuint lvl,
				image_format internal_format, size_t width, size_t height, int border,
				pixel_format pix_form, tex_pixel_type pix_type, const void * pdata);

		//! Generate mipmaps
		/**
		 * http://www.opengl.org/sdk/docs/man4/xhtml/glGenerateMipmap.xml
		 */
		void generate_mipmaps();

	protected:


		//! Generic initialize function
		void initialize();

		//! OpenGL texture type
		texture_type m_tex_type;

		GLPP_START_SAFE_ENUM(param_type)
			BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
			BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
			COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
			COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
			LOD_BIAS = GL_TEXTURE_LOD_BIAS,
			MIN_FILTER = GL_TEXTURE_MIN_FILTER,
			MAG_FILTER = GL_TEXTURE_MAG_FILTER,
			MIN_LOD = GL_TEXTURE_MIN_LOD,
			MAX_LOD = GL_TEXTURE_MAX_LOD,
			MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
			SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
			SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
			SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
			SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
			SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA,
			WRAP_S = GL_TEXTURE_WRAP_S,
			WRAP_T = GL_TEXTURE_WRAP_T,
			WRAP_R = GL_TEXTURE_WRAP_R,
			IMMUTABLE_FORMAT = GL_TEXTURE_IMMUTABLE_FORMAT
		GLPP_END_SAFE_ENUM(param_type)

	private :

		inline void set_parami(param_type param, GLint val) {
			bind();
			::glTexParameteri(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), (GLint)val);
		}

		inline void set_paramf(param_type param, GLfloat val) {
			bind();
			::glTexParameteri(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), (GLfloat)val);
		}

		inline void set_paramiv(param_type param, GLint * val) {
			bind();
			::glTexParameteriv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), val);
		}

		inline void set_paramfv(param_type param, GLfloat * val) {
			bind();
			::glTexParameterfv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), val);
		}

		inline GLint get_parami(param_type param) const{
			bind();
			GLint val;
			::glGetTexParameteriv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), &val);
			return val;
		}

		inline void get_paramiv(param_type param, GLint * pval) const{
			bind();
			::glGetTexParameteriv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), pval);
		}

		inline GLfloat get_paramf(param_type param) const {
			bind();
			GLfloat val;
			::glGetTexParameterfv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), &val);
			return val;
		}

		inline void get_paramfv(param_type param, GLfloat * pval) const {
			bind();
			::glGetTexParameterfv(GLPP_CAST_TO_SCALAR(GLenum, type()), GLPP_CAST_TO_SCALAR(GLenum, param), pval);
		}

	};
}

#endif
