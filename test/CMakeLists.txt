add_executable(test_multiply
    test_multiply.cpp
)

target_link_libraries(test_multiply
    PUBLIC
    multiply_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_multiply)
