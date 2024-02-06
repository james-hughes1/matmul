#include <gtest/gtest.h>
#include <vector>
#include <bitset>
#include "multiply.h"

TEST(multiply, scalar_matrix_case) {
    std::vector<double> test_matrix(6);
    for (int i=0; i<6; i++) {
        if (i % 3 == 2) {
            test_matrix[i] = 2;
        } else {
            test_matrix[i] = 1;
        }
    }
    EXPECT_DOUBLE_EQ(multiply::matmul(test_matrix)[2], 4.0) << "Multiplying two 1x1 matrices failed.";
}

TEST(multiply, read_valid) {
    std::vector<double> test_matrix(6);
    for (int i=0; i<6; i++) {
        if (i % 3 == 2) {
            test_matrix[i] = 2;
        } else {
            test_matrix[i] = 1;
        }
    }
    EXPECT_DOUBLE_EQ(multiply::read_matrix("test/Matrix_Test_A_input.txt")[21], 1.0) << "Reading in a pair of well-defined matrices failed.";
}

TEST(multiply, multiply_valid) {
    std::vector<double> test_matrix_A = multiply::read_matrix("test/Matrix_Test_A_input.txt");
    EXPECT_DOUBLE_EQ(multiply::matmul(test_matrix_A)[6], 72.0) << "Multiplying a pair of well-defined matrices failed.";
}

TEST(multiply, multiply_invalid) {
    std::vector<double> test_matrix_B = multiply::read_matrix("test/Matrix_Test_B_input.txt");
    EXPECT_DOUBLE_EQ(multiply::matmul(test_matrix_B)[10], 1.0) << "Multiplying a mis-matched pair of matrices doesn't throw the right error.";
}