#[[
  Find WEBSOCKETS
  This module finds an installed uWebSockets and libuSockets package.

  It sets the following variables:
    WEBSOCKETS_FOUND       - Set to false, or undefined, if uWebSockets and libuSockets isn't found.
    WEBSOCKETS_INCLUDE_DIR - The uWebSockets include directory.
    WEBSOCKETS_LIBRARY     - The libuSockets library to link against.
]]

find_path(WEBSOCKETS_INCLUDE_DIR uWebSockets)
find_library(WEBSOCKETS_LIBRARY NAMES uSockets)

if(WEBSOCKETS_INCLUDE_DIR AND WEBSOCKETS_LIBRARY)
    set(WEBSOCKETS_FOUND TRUE)
endif(WEBSOCKETS_INCLUDE_DIR AND WEBSOCKETS_LIBRARY)

if(WEBSOCKETS_FOUND)

    # show which libuSockets was found only if not quiet
    if(NOT WEBSOCKETS_FIND_QUIETLY)
        message(STATUS "Found libuSockets: ${WEBSOCKETS_LIBRARY}")
    endif(NOT WEBSOCKETS_FIND_QUIETLY)

else(WEBSOCKETS_FOUND)

    # fatal error if libuSockets is required but not found
    if(WEBSOCKETS_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find libuSockets")
    endif(WEBSOCKETS_FIND_REQUIRED)

endif(WEBSOCKETS_FOUND)