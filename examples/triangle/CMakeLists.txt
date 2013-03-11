add_executable(glpp_example_triangle main.cpp)
target_link_libraries (glpp_example_triangle
    examples_common
    glpp
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLUT_glut_LIBRARY}
)

install (TARGETS glpp_example_triangle 
	RUNTIME DESTINATION share/glpp/examples)