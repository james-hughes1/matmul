add_subdirectory(multiply)
add_subdirectory(timing)

add_executable(main main.cpp)
add_executable(parallel parallel.cpp)
ClangFormat(main .)
ClangFormat(parallel .)

target_link_libraries(main PRIVATE multiply_lib)
target_link_libraries(main PRIVATE timing_lib)

target_link_libraries(parallel PRIVATE multiply_lib)
target_link_libraries(parallel PRIVATE timing_lib)

find_package(MPI REQUIRED)
target_link_libraries(parallel PUBLIC MPI::MPI_CXX)
