add_executable(glpp_example_texture main.cpp)
target_link_libraries(glpp_example_texture
    examples_common
    glpp
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${GLUT_glut_LIBRARY}
    ${FREEIMAGE_LIBRARY}
    ${FREEIMAGEPLUS_LIBRARY}
)

install (TARGETS glpp_example_texture 
	RUNTIME DESTINATION share/glpp/examples)