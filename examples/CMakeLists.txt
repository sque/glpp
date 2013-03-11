if (ASSIMP_FOUND AND Boost_FOUND AND FREEIMAGE_FOUND AND GLM_FOUND)
    include_directories(
        ${ASSIMP_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${FREEIMAGE_INCLUDE_DIR}
    )

    add_subdirectory(common)
    add_subdirectory(resources)
    
    add_subdirectory(lighting_phong)
    add_subdirectory(texture)
    add_subdirectory(rtt)
    add_subdirectory(mrt)
    add_subdirectory(triangle)
endif()
