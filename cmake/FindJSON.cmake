#[[
  Find JSON
  This module finds an installed nlohmann/json package.

  It sets the following variables:
    JSON_FOUND       - Set to false, or undefined, if nlohmann/json isn't found.
    JSON_INCLUDE_DIR - The nlohmann/json include directory.
]]

find_path(JSON_INCLUDE_DIR nlohmann/json.hpp)

if(JSON_INCLUDE_DIR)
  set(JSON_FOUND TRUE)
endif(JSON_INCLUDE_DIR)

if(JSON_FOUND)

  # show which nlohmann/json was found only if not quiet
  if(NOT JSON_FIND_QUIETLY)
    message(STATUS "Found nlohmann/json: ${JSON_INCLUDE_DIR}")
  endif(NOT JSON_FIND_QUIETLY)

else(JSON_FOUND)

  # fatal error if nlohmann/json is required but not found
  if(JSON_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find nlohmann/json")
  endif(JSON_FIND_REQUIRED)

endif(JSON_FOUND)
