add_library(multiply_lib
    STATIC
    multiply.cpp
    method1.cpp
    method2.cpp
    method3.cpp
)

target_include_directories(multiply_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
