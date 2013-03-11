# - Try to find Assimp
# Once done, this will define
#
#  ASSIMP_FOUND - system has Assimp
#  ASSIMP_INCLUDE_DIR - the Assimp include directory
#  ASSIMP_LIBRARY - the Assimp library

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
    pkg_check_modules(PKG_ASSIMP QUIET assimp)
endif()

find_library(ASSIMP_LIBRARY
    NAMES assimp
    HINTS ${PKG_ASSIMP_LIBRARY_DIRS} ${PKG_ASSIMP_LIBDIR}
)

find_path(ASSIMP_INCLUDE_DIR
    NAMES assimp.h ai_assert.h
    HINTS ${PKG_ASSIMP_INCLUDE_DIRS} ${PKG_ASSIMP_INCLUDEDIR}
    PATH_SUFFIXES assimp
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Assimp DEFAULT_MSG ASSIMP_LIBRARY ASSIMP_INCLUDE_DIR)
mark_as_advanced(ASSIMP_LIBRARY ASSIMP_INCLUDE_DIR)
