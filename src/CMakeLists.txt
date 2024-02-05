add_subdirectory(multiply)

add_executable(main main.cpp)
ClangFormat(main .)

target_link_libraries(main PRIVATE multiply_lib)
