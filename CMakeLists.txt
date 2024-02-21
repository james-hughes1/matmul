cmake_minimum_required(VERSION 3.15...3.26)

project(Matrix_Multiplication
    VERSION 1.0
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

include(Testing)
include(Doxygen)
include(ClangFormat)

Doxygen(src docs)

add_subdirectory(src)
add_subdirectory(test)
