include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/src
)

file(GLOB header
    "*.h"
)
file(GLOB src
    "*.c"
    "../src/*.c"
)

if (build_dbcc)
add_executable(dbcc ${header} ${src})
endif()