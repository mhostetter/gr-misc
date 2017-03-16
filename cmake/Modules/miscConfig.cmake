INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MISC misc)

FIND_PATH(
    MISC_INCLUDE_DIRS
    NAMES misc/api.h
    HINTS $ENV{MISC_DIR}/include
        ${PC_MISC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MISC_LIBRARIES
    NAMES gnuradio-misc
    HINTS $ENV{MISC_DIR}/lib
        ${PC_MISC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MISC DEFAULT_MSG MISC_LIBRARIES MISC_INCLUDE_DIRS)
MARK_AS_ADVANCED(MISC_LIBRARIES MISC_INCLUDE_DIRS)

