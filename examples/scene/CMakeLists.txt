add_executable (glpp_example_scene main.cpp)
target_link_libraries (glpp_example_scene
    examples_common
    glpp
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${GLUT_glut_LIBRARY}
)

install (TARGETS glpp_example_scene 
	RUNTIME DESTINATION share/glpp/examples)