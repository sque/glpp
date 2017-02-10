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

#ifndef GLPP_CXX11_SUPPORT_HPP_INCLUDED
#define GLPP_CXX11_SUPPORT_HPP_INCLUDED

#include <initializer_list>

// Use stdlib shared_pointer
#define GLPP_SHARED_PTR( TYPE ) std::shared_ptr< TYPE >

namespace glpp{
	//! C++11 implementation of noncopyable pattern
	struct noncopyable {
		noncopyable(){}
		~noncopyable(){}

		noncopyable(noncopyable &) = delete;
		noncopyable& operator=(noncopyable &) = delete;
	};
};

// Type safe enum classes
#define GLPP_START_SAFE_ENUM(name) \
	enum class name {

#define GLPP_END_SAFE_ENUM(name) };

#define GLPP_CAST_TO_SCALAR(scalar_type, var) \
		static_cast<scalar_type>(var)

#define GLPP_CAST_TO_SAFE_ENUM(safe_type, var) \
		(safe_type)(var)
#endif
