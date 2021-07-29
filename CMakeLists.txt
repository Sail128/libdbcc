cmake_minimum_required(VERSION 3.16)

project("libdbcc" VERSION 0.1.0)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

option(build_dbcc "Build converter utility" on)

# message(STATUS ${CMAKE_BINARY_DIR})

include_directories("include") # add the include directory
add_subdirectory(src) # add the source directory
add_subdirectory(dbcc)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)