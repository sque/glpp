set(glpp_SRCS
./utils/info.cpp
./logicop_unit.cpp
./context.cpp
./program.cpp
./scissor_test_unit.cpp
./blend_unit.cpp
./stencil_test_unit.cpp
./capabilities_unit.cpp
./depth_test_unit.cpp
./texture_unit.cpp
./shader.cpp
./frame_buffer.cpp
./uniform_block.cpp
./global_uniform.cpp
./buffer.cpp
./face_cull_unit.cpp
./render_buffer.cpp
./uniform.cpp
./texture.cpp
./vertex_array.cpp
 
)

set(glpp_HEADERS
./exception.hpp
./global_uniform.hpp
./frame_buffer.hpp
./context.hpp
./capabilities_unit.hpp
./uniform.hpp
./render_buffer.hpp
./base.hpp
./buffer.hpp
./glpp.hpp
./boost_support.hpp
./types.hpp
./depth_test_unit.hpp
./scissor_test_unit.hpp
./uniform_block.hpp
./shader.hpp
./texture_unit.hpp
./program.hpp
./stencil_test_unit.hpp
./vertex_array.hpp
./cxx11_support.hpp
./blend_unit.hpp
./logicop_unit.hpp
./texture.hpp
./setup.hpp
./face_cull_unit.hpp
)

set(glpp_utils_HEADERS
    utils/info.hpp
)

add_library(glpp ${glpp_SRCS})
target_link_libraries(glpp 
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
)

install(TARGETS glpp DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT glpp)
install(FILES ${glpp_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glpp COMPONENT glpp-dev)
install(FILES ${glpp_utils_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glpp/utils COMPONENT glpp-dev)
