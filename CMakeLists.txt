project(glpp)
cmake_minimum_required(VERSION 2.8.5)

# put our custom modules into cmake's search path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# options
option(BUILD_EXAMPLES "Build glpp examples." ON)
option(FORCE_CXX11 "Force C++11 standard." OFF)

# find dependencies
include(MacroLogFeature)
include(GNUInstallDirs)

find_package(OpenGL)
macro_log_feature(OPENGL_FOUND "OpenGL" "Required to build glpp" "http://www.opengl.org" TRUE)

find_package(GLUT)
macro_log_feature(GLUT_FOUND "FreeGLUT" "Required to build glpp" "http://freeglut.sourceforge.net/" TRUE)

find_package(GLEW)
macro_log_feature(GLEW_FOUND "GLEW" "Required to build glpp" "http://glew.sourceforge.net/" TRUE)

find_package(GLM)
macro_log_feature(GLM_FOUND "GLM" "Required to build examples" "http://glm.g-truc.net/" FALSE)

find_package(FreeImage)
macro_log_feature(FREEIMAGE_FOUND "FreeImage" "Required for the examples" "http://freeimage.sourceforge.net/" FALSE)

find_package(Boost)
macro_log_feature(Boost_FOUND "Boost" "Required for the examples" "http://www.boost.org/" FALSE)

find_package(Assimp)
macro_log_feature(ASSIMP_FOUND "Assimp" "Required for the examples" "http://assimp.sourceforge.net/" FALSE)

# common flags for all the project
if (CMAKE_COMPILER_IS_GNUCXX)
	execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE CXX_VERSION)
	if (CXX_VERSION VERSION_GREATER 4.6 OR CXX_VERSION VERSION_EQUAL 4.6)
	        message(STATUS "GCC Version >= 4.6, enabling C++11")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
	endif()
endif()

if (FORCE_CXX11)
	add_definitions(-DGLPP_FORCE_CXX11)
endif()

if(NOT WIN32)
    add_definitions(-fPIC)
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

macro_display_feature_log()
