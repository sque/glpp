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

#ifndef GLPP_BOOST_SUPPORT_HPP_INCLUDED
#define GLPP_BOOST_SUPPORT_HPP_INCLUDED

// Use boost shared_pointer implementation
#include <boost/shared_ptr.hpp>
#define GLPP_SHARED_PTR( TYPE ) boost::shared_ptr< TYPE >

// Use boost noncopyable pattern
#include <boost/noncopyable.hpp>
namespace glpp {	typedef boost::noncopyable noncopyable;	};

// Create scoped enumeration
namespace glpp {
	namespace detail {
		template<class Def, class StorageType = typename Def::type>
		struct safe_enum: public Def {

			typedef typename Def::type type;
			typedef StorageType storage_type;

			storage_type val;

		public:

			safe_enum() {}

			safe_enum(type v) : val(v) {}

			storage_type underlying() const {
				return val;
			}

			bool operator ==(const safe_enum & s) const {
				return this->val == s.val;
			}
			bool operator !=(const safe_enum & s) const {
				return this->val != s.val;
			}
			bool operator <(const safe_enum & s) const {
				return this->val < s.val;
			}
			bool operator <=(const safe_enum & s) const {
				return this->val <= s.val;
			}
			bool operator >(const safe_enum & s) const {
				return this->val > s.val;
			}
			bool operator >=(const safe_enum & s) const {
				return this->val >= s.val;
			}
		};
	}
}
#define GLPP_START_SAFE_ENUM(name) \
	struct enum_def_##name { \
		enum type {

#define GLPP_END_SAFE_ENUM(name) \
		}; \
	};\
	typedef glpp::detail::safe_enum<enum_def_##name> name;

#define GLPP_CAST_TO_SCALAR(scalar_type, var) \
		static_cast<scalar_type>(var.underlying())

#define GLPP_CAST_TO_SAFE_ENUM(safe_type, var) \
		safe_type((safe_type::type) var)
#endif
