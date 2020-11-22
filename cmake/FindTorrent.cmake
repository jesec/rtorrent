#[[
  Find Torrent
  This module finds an installed libTorrent package.

  It sets the following variables:
    TORRENT_FOUND       - Set to false, or undefined, if libTorrent isn't found.
    TORRENT_INCLUDE_DIR - The libTorrent include directory.
    TORRENT_LIBRARY     - The libTorrent library to link against.
]]

find_path(TORRENT_INCLUDE_DIR torrent/torrent.h)
find_library(TORRENT_LIBRARY NAMES torrent)

if(TORRENT_INCLUDE_DIR AND TORRENT_LIBRARY)
  set(TORRENT_FOUND TRUE)
endif(TORRENT_INCLUDE_DIR AND TORRENT_LIBRARY)

if(TORRENT_FOUND)

  # show which libTorrent was found only if not quiet
  if(NOT Torrent_FIND_QUIETLY)
    message(STATUS "Found libTorrent: ${TORRENT_LIBRARY}")
  endif(NOT Torrent_FIND_QUIETLY)

else(TORRENT_FOUND)

  # fatal error if libTorrent is required but not found
  if(Torrent_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find libTorrent")
  endif(Torrent_FIND_REQUIRED)

endif(TORRENT_FOUND)
