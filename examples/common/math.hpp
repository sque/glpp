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

#ifndef GLPP_TESTS_MATH_HPP_INCLUDED
#define GLPP_TESTS_MATH_HPP_INCLUDED

#include <ogl/ogl.hpp>
namespace glpp {

	template<typename T, GLuint D>
	class basic_vector {
	public:
		typedef T value_type;

		value_type val[D];

		static const GLuint total_elements = D;

		value_type & operator[](GLuint index) {
			return val[index];
		}

		basic_vector operator+(const basic_vector & r) {
			basic_vector tmp(*this);
			for(int i = 0;i < total_elements;i++) {
				tmp.val[i] += r.val[i];
			}
			return tmp;
		}
	};

	typedef basic_vector<GLfloat, 2> vector2;
	typedef basic_vector<GLfloat, 3> vector3;
	typedef basic_vector<GLfloat, 4> vector4;

	template<typename T, GLuint N, GLuint M>
	class basic_matrix {
	public:
		typedef T value_type;

		static const GLuint total_columns = N;
		static const GLuint total_rows = M;

		value_type val[M][N];

		basic_matrix operator*(const basic_matrix & r) {
			basic_matrix mul;

			for(int y = 0; y < total_rows; y++){
				for(int x = 0;x < total_columns; x++) {
					mul.val[y][x] =
				}
			}
			mul.val[0][0] = val[0][0] * r.val[0][0] + val[0][1] * r.val[1][0] + val[0][2] * r.val[2][0];
			mul.val[0][1] = val[0][0] * r.val[0][1] + val[0][1] * r.val[1][1] + val[0][2] * r.val[2][1];
			mul.val[0][2] = val[0][0] * r.val[0][2] + val[0][1] * r.val[1][2] + val[0][2] * r.val[2][2];

			mul.val[1][0] = val[1][0] * r.val[0][0] + val[1][1] * r.val[1][0] + val[1][2] * r.val[2][0];
			mul.val[1][1] = val[1][0] * r.val[0][1] + val[1][1] * r.val[1][1] + val[1][2] * r.val[2][1];
			mul.val[1][2] = val[1][0] * r.val[0][2] + val[1][1] * r.val[1][2] + val[1][2] * r.val[2][2];

			mul.val[2][0] = val[2][0] * r.val[0][0] + val[2][1] * r.val[1][0] + val[2][2] * r.val[2][0];
			mul.val[2][1] = val[2][0] * r.val[0][1] + val[2][1] * r.val[1][1] + val[2][2] * r.val[2][1];
			mul.val[2][2] = val[2][0] * r.val[0][2] + val[2][1] * r.val[1][2] + val[2][2] * r.val[2][2];
			return mul;
		}
	};

	typedef basic_matrix<GLfloat, 4, 4> matrix4;
	typedef basic_matrix<GLfloat, 3, 3> matrix3;
}

#endif
