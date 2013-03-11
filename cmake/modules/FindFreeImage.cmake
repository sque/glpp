# - Try to find FreeImage
# Once done, this will define
#
#  FREEIMAGE_FOUND - system has FreeImage
#  FREEIMAGE_INCLUDE_DIR - the FreeImage include directory
#  FREEIMAGE_LIBRARY - the FreeImage library
#  FREEIMAGEPLUS_LIBRARY - The FreeImagePlus library

find_library(FREEIMAGE_LIBRARY NAMES freeimage)
find_library(FREEIMAGEPLUS_LIBRARY NAMES freeimageplus)
find_path(FREEIMAGE_INCLUDE_DIR FreeImage.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeImage DEFAULT_MSG
    FREEIMAGE_LIBRARY
    FREEIMAGEPLUS_LIBRARY
    FREEIMAGE_INCLUDE_DIR
)
mark_as_advanced(FREEIMAGE_LIBRARY FREEIMAGEPLUS_LIBRARY FREEIMAGE_INCLUDE_DIR)
