add_executable(glpp_example_rtt main.cpp)
target_link_libraries (glpp_example_rtt
    examples_common
    glpp
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLUT_glut_LIBRARY}
	${FREEIMAGE_LIBRARY}
	${FREEIMAGEPLUS_LIBRARY}
)

install (TARGETS glpp_example_rtt
	RUNTIME DESTINATION share/glpp/examples)
