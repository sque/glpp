set(examples_common_SRCS
    post_effects.cpp
    sphere.cpp
    skybox.cpp
    light.cpp
    effect.cpp
    camera.cpp
    cube.cpp
    scene.cpp
    material.cpp
    geometry.cpp
    plane.cpp
)

add_library(examples_common ${examples_common_SRCS})
target_link_libraries(examples_common
    glpp
    ${OPENGL_gl_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${FREEIMAGEPLUS_LIBRARY}
)
