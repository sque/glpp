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

#ifndef GLPP_EXCEPTION_HPP_INCLUDED
#define GLPP_EXCEPTION_HPP_INCLUDED

#include "base.hpp"
#include <stdexcept>

namespace glpp {

	/**
	 * @{
	 * @defgroup exceptions Exceptions
	 * @brief Exceptions defined by GLPP
	 *
	 * GLPP uses exceptions to notify for abnormal behavior on execution path, but
	 * at the same time tries to keep performance equal to using plain old C interface.
	 * All exceptions are inherited from std::exception for the sake of interoperability.
	 * Some exceptions may carry additional information depending the purpose they serve.
	 * @}
	 *
	 */

	//! Base exception class for all GLPP related exceptions
	/**
	 * @ingroup exceptions
	 */
	struct exception: public std::exception {

		//! Error string holder
		std::string m_error_str;

		//! Class is inheritable
		virtual ~exception() throw () {	}

		//! Constructor with error string
		exception(const std::string & error) throw () :
				m_error_str(error) {}

		//! Default constructor
		exception() throw(){};

		//! Return what string
		virtual const char * what() const throw () {
			return m_error_str.c_str();
		}
	};

	//! Exception that wraps an OpenGL error code.
	/**
	 * @ingroup exceptions
	 */
	struct gl_error: public exception {

		//! OpenGL error code
		GLenum m_gl_error;

		//! Construct with the error code
		/**
		 * Error message will be "GL: <human_readable_glerror_code>"
		 */
		gl_error(GLenum error) :
			m_gl_error(error){
			m_error_str = std::string("GL: ") + get_glu_error_str();
		}

		//! Construct with error code and custom message
		/**
		 * Error message will be "GL: <custom_msg> <human_readable_glerror_code>"
		 */
		gl_error(GLenum error, const std::string & custom_msg) :
			m_gl_error(error){
			m_error_str = std::string("GL: ") + custom_msg + std::string(" ")
					+ get_glu_error_str();
		}

		//! Inheritable
		virtual ~gl_error() throw () {	}

	private:
		//! Get human readable string from GLerror code
		const std::string get_glu_error_str() {
			return (const char *) gluErrorString(m_gl_error);
		}
	};

	//! Exception thrown when object cannot be located
	/**
	 * @ingroup exceptions
	 */
	struct object_not_found: public exception {

		//! Construct with the name of object
		/**
		 * Error message will be "Cannot find object with name <name>"
		 */
		object_not_found(const std::string & name) throw (){
			m_error_str = std::string("Cannot find object with name ") + name;
		}

		//! Class is inheritable
		virtual ~object_not_found() throw() {}
	};

	//! Exception thrown when uniform cannot be located
	/**
	 * @ingroup exceptions
	 */
	struct uniform_not_found: public exception {

		//! Construct with name of uniform
		/**
		 * Error message will be "Cannot find uniform with name <name>"
		 */
		uniform_not_found(const std::string & name) throw (){
			m_error_str = std::string("Cannot find uniform with name ") + name;
		}

		//! Class is inheritable
		virtual ~uniform_not_found() throw() {}
	};

	//! Exception thrown when compilation has failed.
	struct compile_error: public exception {

		//! Construct with error message
		compile_error(const std::string & error) throw () :
				exception(error) {}

		//! Class is inheritable
		virtual ~compile_error() throw () {	}
	};

	//! Exception thrown when shader linking has failed
	struct link_error: public exception {

		//! Construct with linking error description
		link_error(const std::string & error) throw () :
				exception(error) {}

		//! Class is inheritable
		virtual ~link_error() throw () {}
	};

	//! Exception thrown when there is no active context
	/**
	 * @ingroup exceptions
	 */
	struct no_active_context: public exception {

		// Default constructor
		/**
		 * Error message will be "No active context."
		 */
		no_active_context() throw() :
			exception("No active context."){
		}

		// Constructor with custom message
		/**
		 * Error message will be "No active context. <error>"
		 */
		no_active_context(const std::string & error) throw() {
			m_error_str = std::string("No active context. " + error);
		}

		//! Class is inheritable
		virtual ~no_active_context() throw() {}
	};

	//! Runtime assertion that there is no error on OpenGL pipeline
	/**
	 * This function whenever executed will check if there is an error produced by previous
	 * OpenGL functions. If the error stack is not clean it will throw an gl_error exception.
	 * http://www.opengl.org/sdk/docs/man4/xhtml/glGetError.xml
	 */
	inline void assert_no_glerror(const std::string & custom_message) throw(gl_error){
		GLenum gerr;
		if ((gerr = glGetError()) != GL_NO_ERROR) {
			throw gl_error(gerr, custom_message);
		}
	}

}
#endif
