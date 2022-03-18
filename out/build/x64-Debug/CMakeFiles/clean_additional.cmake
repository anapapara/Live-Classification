# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\LiveClassification_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\LiveClassification_autogen.dir\\ParseCache.txt"
  "LiveClassification_autogen"
  )
endif()
