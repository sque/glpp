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

#ifndef GLPP_UTILS_DEBUG_HPP_INCLUDED
#define GLPP_UTILS_DEBUG_HPP_INCLUDED

#include "../base.hpp"
#include "../context.hpp"

#if (GLPP_LANG != GLPP_LANG_CXX0X) && (GLPP_LANG != GLPP_LANG_CXX11)
#	error Info depends on C++11 version.
#endif

namespace glpp {
namespace utils {

	template<class E>
	class bitflags {
	public:

		typedef E opt;

		typedef unsigned base_type;

		bitflags();

		bitflags (E val):
			m_val(val) {
		}

		bitflags(std::initializer_list<E> flags) :
			m_val(E(0)){
			for(auto f : flags) {
				m_val = E((base_type)m_val | (base_type)f);
			}
		}

		base_type get_base() const{
			return (base_type)m_val;
		}

		bitflags operator~() const {
			base_type inter = ~get_base();
			return bitflags((E)inter);
		}

		bitflags operator&(const bitflags & r) const {
			return bitflags(E(get_base() & r.get_base()));
		}

		bitflags operator|(const bitflags & r) const {
			return bitflags(E(get_base() | r.get_base()));
		}

		bool has_flag(E val) const {
			return (base_type(m_val) & base_type(val)) != 0;
		}

		operator E () {
			return m_val;
		}

		static bitflags _and(E lv, E rv) {
			return bitflags(lv) & bitflags(rv);
		}

	protected:
		E m_val;
	};

	enum class info_filter : unsigned{
		NONE = 0,
		LIMITS = 1,
		EXTENSIONS = 2,
		COMPRESSED_FORMATS = 4,
		BINARY_FORMATS = 8,
		ALL = BINARY_FORMATS | COMPRESSED_FORMATS | EXTENSIONS | LIMITS
	};

	//! Get information about a context
	extern std::string info(context & ctx, bitflags<info_filter> filter = info_filter::ALL);
}
}


#endif
