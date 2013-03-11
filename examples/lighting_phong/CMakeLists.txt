add_executable (glpp_example_lighting_phong main.cpp)
target_link_libraries (glpp_example_lighting_phong
    examples_common
    glpp
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLUT_LIBRARIES}
)

install (TARGETS glpp_example_lighting_phong 
	RUNTIME DESTINATION share/glpp/examples)
