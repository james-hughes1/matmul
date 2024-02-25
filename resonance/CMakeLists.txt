add_executable(resonance resonance.cpp)

target_link_libraries(resonance
    PUBLIC
    multiply_lib
    timing_lib
)
